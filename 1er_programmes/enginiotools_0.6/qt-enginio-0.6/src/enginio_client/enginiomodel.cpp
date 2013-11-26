/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://qt.digia.com/contact-us
**
** This file is part of the Enginio Qt Client Library.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#include "enginiomodel.h"
#include "enginioreply.h"
#include "enginioclient_p.h"
#include "enginiofakereply_p.h"
#include "enginiodummyreply_p.h"
#include "enginiobackendconnection_p.h"

#include <QtCore/qobject.h>
#include <QtCore/qvector.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qdatetime.h>
#include <QtCore/quuid.h>

enum {
    DeletedRow = -3,
    NoHintRow = -4,
    InvalidRow = NoHintRow
};

struct EnginioModelPrivateAttachedData
{
    uint ref;
    int row;
    QString id;
    EnginioReply *createReply;
    EnginioModelPrivateAttachedData(int initRow = DeletedRow, const QString &initId = QString())
        : ref()
        , row(initRow)
        , id(initId)
        , createReply()
    {}
};
Q_DECLARE_TYPEINFO(EnginioModelPrivateAttachedData, Q_MOVABLE_TYPE);

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const EnginioModelPrivateAttachedData &a)
{
    dbg.nospace() << "EnginioModelPrivateAttachedData(ref:";
    dbg.nospace() << a.ref << ", row: "<< a.row << ", synced: " << (a.ref == 0) << ", id: " << a.id;
    dbg.nospace() << ')';
    return dbg.space();
}
#endif

class AttachedDataContainer
{
    typedef int Row;
    typedef int StorageIndex;
    typedef QString ObjectId;
    typedef QString RequestId;
    typedef EnginioModelPrivateAttachedData AttachedData;

    typedef QHash<Row, StorageIndex> RowIndex;
    RowIndex _rowIndex;

    typedef QHash<ObjectId, StorageIndex> ObjectIdIndex;
    ObjectIdIndex _objectIdIndex;

    typedef QHash<RequestId, QPair<int /*ref*/, StorageIndex> > RequestIdIndex;
    RequestIdIndex _requestIdIndex;

    typedef QHash<StorageIndex, AttachedData> Storage;
    QVector<AttachedData> _storage; // TODO replace by something smarter so we can use pointers instead of index.

    const static int InvalidStorageIndex;

    StorageIndex append(const AttachedData &data)
    {
        _storage.append(data);
        StorageIndex idx = _storage.count() - 1;
        _rowIndex.insert(data.row, idx);
        _objectIdIndex.insert(data.id, idx);
        return idx;
    }

public:
    bool contains(const ObjectId &id) const
    {
        return _objectIdIndex.contains(id);
    }

    Row rowFromObjectId(const ObjectId &id) const
    {
        Q_ASSERT(contains(id));
        StorageIndex idx = _objectIdIndex.value(id, InvalidStorageIndex);
        return idx == InvalidStorageIndex ? InvalidRow : _storage[idx].row;
    }

    Row rowFromRequestId(const RequestId &id) const
    {
        StorageIndex idx = _requestIdIndex.value(id, qMakePair(0, InvalidStorageIndex)).second;
        return idx == InvalidStorageIndex ? InvalidRow : _storage[idx].row;
    }

    bool isSynced(Row row) const
    {
        return _storage[_rowIndex.value(row)].ref == 0;
    }

    void updateAllDataAfterRowRemoval(const int row) {
        _rowIndex.clear();
        _rowIndex.reserve(_storage.count());
        for (StorageIndex i = 0; i < _storage.count() ; ++i) {
            AttachedData &data = _storage[i];
            if (data.row > row)
                --data.row;
            else if (data.row == row)
                data.row = DeletedRow;
            _rowIndex.insert(data.row, i);
        }
    }

    AttachedData &ref(const ObjectId &id, Row row)
    {
        StorageIndex idx = _objectIdIndex.value(id, InvalidStorageIndex);
        if (idx == InvalidStorageIndex) {
            AttachedData data(row, id);
            idx = append(data);
        }
        AttachedData &data = _storage[idx];
        ++data.ref;
        Q_ASSERT(_storage[idx].ref == 1 || _storage[idx].row == row);
        data.row = row;
        return data;
    }

    AttachedData &ref(Row row)
    {
        StorageIndex idx = _rowIndex.value(row, InvalidStorageIndex);
        Q_ASSERT(idx != InvalidStorageIndex);
        AttachedData &data = _storage[idx];
        ++data.ref;
        return data;
    }

    AttachedData &deref(const ObjectId &id)
    {
        StorageIndex idx = _objectIdIndex.value(id, InvalidStorageIndex);
        Q_ASSERT(idx != InvalidStorageIndex);
        AttachedData &attachedData = _storage[idx];
        if (!--attachedData.ref && id[0] == 't') {
            // TODO it is last ref to a tmp id we should remove it
        }
        return attachedData;
    }

    void insert(const AttachedData &data)
    {
        _storage.append(data);
        StorageIndex idx = _storage.count() - 1;
        _rowIndex.insert(data.row, idx);
        _objectIdIndex.insert(data.id, idx);
    }

    void insertRequestId(const RequestId &id, Row row)
    {
        StorageIndex idx = _rowIndex.value(row, InvalidStorageIndex);
        Q_ASSERT(idx != InvalidStorageIndex);
        _requestIdIndex.insert(id, qMakePair(2, idx));
    }

    /*!
      \internal
      returns true if the request was already handled
    */
    bool markRequestIdAsHandled(const RequestId &id)
    {
        RequestIdIndex::iterator::reference value = _requestIdIndex[id];
        if (value.first) {
            if (--value.first <= 0) {
                _requestIdIndex.remove(id);
                return true;
            }
        } else {
            _requestIdIndex.remove(id);
        }
        return false;
    }

    void initFromArray(const QJsonArray &array)
    {
        const int count = array.count();
        _storage.clear();
        _rowIndex.clear();
        _objectIdIndex.clear();

        _storage.reserve(count);
        _rowIndex.reserve(count);
        _objectIdIndex.reserve(count);

        for (int row = 0; row < count; ++row) {
            QString id = array[row].toObject()[EnginioString::id].toString();
            Q_ASSERT(!id.isEmpty());
            AttachedData data(row, id);
            _storage.append(data);
            _rowIndex.insert(row, row);
            _objectIdIndex.insert(id, row);
        }
    }
};

const int AttachedDataContainer::InvalidStorageIndex = InvalidRow;

class EnginioModelPrivate {
    QJsonObject _query;
    EnginioClient *_enginio;
    EnginioClient::Operation _operation;
    EnginioModel *q;
    QVector<QMetaObject::Connection> _connections;

    const static int IncrementalModelUpdate;
    typedef EnginioModelPrivateAttachedData AttachedData;
    AttachedDataContainer _attachedData;
    int _latestRequestedOffset;
    bool _canFetchMore;

    unsigned _rolesCounter;
    QHash<int, QString> _roles;

    QJsonArray _data; // TODO replace by a sparse array, and add laziness

    class NotificationObject {
        // connection object it can be:
        // - null if not yet created
        // - -1 if notifications where disabled with EnginioModel::disableNotifications()
        // - valid pointer to connection object
        EnginioBackendConnection *_connection;

        struct NotificationReceived
        {
            EnginioModelPrivate *model;

            void operator ()(QJsonObject data)
            {
                model->receivedNotification(data);
            }
        };
        void removeConnection()
        {
            if (*this) {
                _connection->close();
                delete _connection;
            }
        }

    public:
        NotificationObject()
            : _connection()
        {}

        ~NotificationObject()
        {
            removeConnection();
        }

        operator EnginioBackendConnection*()
        {
            return qintptr(_connection) != -1 ? _connection : 0;
        }

        void disable()
        {
            removeConnection();
            _connection = (EnginioBackendConnection*)-1;
        }

        void connectToBackend(EnginioModelPrivate *model, EnginioClient *enginio, const QJsonObject &filter)
        {
            if (qintptr(_connection) == -1)
                return;
            Q_ASSERT(model && enginio);
            if (enginio->serviceUrl() != EnginioString::stagingEnginIo)
                return;  // TODO it allows to use notification only on staging
            removeConnection(); // TODO reuse the connecton object
            _connection = new EnginioBackendConnection;
            NotificationReceived receiver = { model };
            QObject::connect(_connection, &EnginioBackendConnection::dataReceived, receiver);
            _connection->connectToBackend(enginio, filter);
        }
    } _notifications;

    class EnginioDestroyed
    {
        EnginioModelPrivate *model;
    public:
        EnginioDestroyed(EnginioModelPrivate *m)
            : model(m)
        {
            Q_ASSERT(m);
        }
        void operator ()()
        {
            model->setEnginio(0);
        }
    };

    struct FinishedRemoveRequest
    {
        EnginioModelPrivate *model;
        const QString id;
        void operator ()(const EnginioReply *reply)
        {
            model->finishedRemoveRequest(reply, id);
        }
    };

    struct FinishedUpdateRequest
    {
        EnginioModelPrivate *model;
        const QString id;
        const QJsonObject oldValue;
        void operator ()(const EnginioReply *reply)
        {
            model->finishedUpdateRequest(reply, id, oldValue);
        }
    };

    struct FinishedCreateRequest
    {
        EnginioModelPrivate *model;
        const QString tmpId;
        void operator ()(const EnginioReply *reply)
        {
            model->finishedCreateRequest(reply, tmpId);
        }
    };

    struct FinishedFullQueryRequest
    {
        EnginioModelPrivate *model;
        void operator ()(const EnginioReply *reply)
        {
            model->finishedFullQueryRequest(reply);
        }
    };

    struct FinishedIncrementalUpdateRequest
    {
        EnginioModelPrivate *model;
        const QJsonObject query;
        void operator ()(const EnginioReply *reply)
        {
            model->finishedIncrementalUpdateRequest(reply, query);
        }
    };

    class QueryChanged
    {
        EnginioModelPrivate *model;
    public:
        QueryChanged(EnginioModelPrivate *m)
            : model(m)
        {
            Q_ASSERT(m);
        }

        void operator ()()
        {
            model->execute();
        }
    };

public:
    EnginioModelPrivate(EnginioModel *q_ptr)
        : _enginio(0)
        , _operation()
        , q(q_ptr)
        , _latestRequestedOffset(0)
        , _canFetchMore(false)
        , _rolesCounter(EnginioModel::SyncedRole)
    {
        QObject::connect(q, &EnginioModel::queryChanged, QueryChanged(this));
        QObject::connect(q, &EnginioModel::operationChanged, QueryChanged(this));
        QObject::connect(q, &EnginioModel::enginioChanged, QueryChanged(this));
    }

    ~EnginioModelPrivate()
    {
        foreach (const QMetaObject::Connection &connection, _connections)
            QObject::disconnect(connection);
    }

    void disableNotifications()
    {
        _notifications.disable();
    }

    void receivedNotification(QJsonObject data)
    {
        const QJsonObject origin = data[EnginioString::origin].toObject();
        const QString requestId = origin[EnginioString::apiRequestId].toString();
        if (_attachedData.markRequestIdAsHandled(requestId))
            return; // request was handled

        QJsonObject object = data[EnginioString::data].toObject();
        QString event = data[EnginioString::event].toString();
        if (event == EnginioString::update) {
            receivedUpdateNotification(object);
        } else if (event == EnginioString::_delete) {
            receivedRemoveNotification(object);
        } else  if (event == EnginioString::create) {
            const int rowHint = _attachedData.rowFromRequestId(requestId);
            if (rowHint != NoHintRow)
                receivedUpdateNotification(object, QString(), rowHint);
            else
                receivedCreateNotification(object);
        }
    }

    void receivedRemoveNotification(const QJsonObject &object, int rowHint = NoHintRow)
    {
        int row = rowHint;
        if (rowHint == NoHintRow) {
            QString id = object[EnginioString::id].toString();
            if (Q_UNLIKELY(!_attachedData.contains(id))) {
                // removing not existing object
                return;
            }
            row = _attachedData.rowFromObjectId(id);
        }
        if (Q_UNLIKELY(row == DeletedRow))
            return;

        q->beginRemoveRows(QModelIndex(), row, row);
        _data.removeAt(row);
        // we need to updates rows in _attachedData
        _attachedData.updateAllDataAfterRowRemoval(row);
        q->endRemoveRows();
    }

    void receivedUpdateNotification(const QJsonObject &object, const QString &idHint = QString(), int row = NoHintRow)
    {
        // update an existing object
        if (row == NoHintRow) {
            QString id = idHint.isEmpty() ? object[EnginioString::id].toString() : idHint;
            Q_ASSERT(_attachedData.contains(id));
            row = _attachedData.rowFromObjectId(id);
        }
        if (Q_UNLIKELY(row == DeletedRow))
            return;
        Q_ASSERT(row >= 0);

        QJsonObject current = _data[row].toObject();
        QDateTime currentUpdateAt = QDateTime::fromString(current[EnginioString::updatedAt].toString(), Qt::ISODate);
        QDateTime newUpdateAt = QDateTime::fromString(object[EnginioString::updatedAt].toString(), Qt::ISODate);
        if (newUpdateAt < currentUpdateAt) {
            // we already have a newer version
            return;
        }
        if (_data[row].toObject()[EnginioString::id].toString().isEmpty()) {
            // Create and update may go through the same code path because
            // the model already have a dummy item. No id means that it
            // is a dummy item.
            const QString newId = object[EnginioString::id].toString();
            AttachedData newData(row, newId);
            _attachedData.insert(newData);
        }
        if (_data.count() == 1) {
            q->beginResetModel();
            _data.replace(row, object);
            syncRoles();
            q->endResetModel();
        } else {
            _data.replace(row, object);
            emit q->dataChanged(q->index(row), q->index(row));
        }
    }

    void receivedCreateNotification(const QJsonObject &object)
    {
        // create a new object
        QString id = object[EnginioString::id].toString();
        Q_ASSERT(!_attachedData.contains(id));
        AttachedData data;
        data.row = _data.count();
        data.id = id;
        q->beginInsertRows(QModelIndex(), _data.count(), _data.count());
        _attachedData.insert(data);
        _data.append(object);
        q->endInsertRows();
    }

    EnginioClient *enginio() const Q_REQUIRED_RESULT
    {
        return _enginio;
    }

    void setEnginio(const EnginioClient *enginio)
    {
        if (_enginio) {
            foreach(const QMetaObject::Connection &connection, _connections)
                QObject::disconnect(connection);
            _connections.clear();
        }
        _enginio = const_cast<EnginioClient*>(enginio);
        if (_enginio) {
            _connections.append(QObject::connect(_enginio, &QObject::destroyed, EnginioDestroyed(this)));
            _connections.append(QObject::connect(_enginio, &EnginioClient::backendIdChanged, QueryChanged(this)));
            _connections.append(QObject::connect(_enginio, &EnginioClient::backendSecretChanged, QueryChanged(this)));
        }
        emit q->enginioChanged(_enginio);
    }

    QJsonObject query() Q_REQUIRED_RESULT
    {
        return _query;
    }

    EnginioReply *append(const QJsonObject &value)
    {
        QJsonObject object(value);
        QString temporaryId = QString::fromLatin1("tmp") + QUuid::createUuid().toString();
        object[EnginioString::objectType] = _query[EnginioString::objectType]; // TODO think about it, it means that not all queries are valid
        EnginioReply *ereply = _enginio->create(object, _operation);
        FinishedCreateRequest finishedRequest = { this, temporaryId };
        QObject::connect(ereply, &EnginioReply::finished, finishedRequest);
        object[EnginioString::id] = temporaryId;
        const int row = _data.count();
        AttachedData data(row, temporaryId);
        data.ref = 1;
        data.createReply = ereply;
        if (!row) { // the first item need to update roles
            q->beginResetModel();
            _attachedData.insert(data);
            _data.append(value);
            syncRoles();
            q->endResetModel();
        } else {
            q->beginInsertRows(QModelIndex(), _data.count(), _data.count());
            _attachedData.insert(data);
            _data.append(value);
            q->endInsertRows();
        }
        _attachedData.insertRequestId(ereply->requestId(), row);
        return ereply;
    }

    struct SwapNetworkReplyBase
    {
        EnginioReply *_reply;
        EnginioModelPrivate *_model;
        QJsonObject _object;
        QString _tmpId;

        void markAsError(QByteArray msg)
        {
            EnginioClientPrivate *client = EnginioClientPrivate::get(_model->_enginio);
            EnginioFakeReply *nreply = new EnginioFakeReply(client, constructErrorMessage(msg));
            _reply->setNetworkReply(nreply);
        }

        int getCurrentRow() { return _model->_attachedData.deref(_tmpId).row; }

        QString getAndSetCurrentId(EnginioReply *finishedCreateReply)
        {
            QString id = finishedCreateReply->data()[EnginioString::id].toString();
            Q_ASSERT(!id.isEmpty());
            _object[EnginioString::id] = id;
            return id;
        }

        void swapNetworkReply(EnginioReply *ereply)
        {
            _reply->swapNetworkReply(ereply);
            ereply->deleteLater();
        }
    };

    struct SwapNetworkReplyForRemove
    {
        SwapNetworkReplyBase d;
        void operator ()(EnginioReply *finishedCreateReply)
        {
            if (finishedCreateReply->isError()) {
                d.markAsError(QByteArrayLiteral("Dependent create query failed, so object coudl not be removed"));
            } else {
                const int row = d.getCurrentRow();
                QString id = d.getAndSetCurrentId(finishedCreateReply);
                FinishedRemoveRequest finishedRequest = { d._model, id };
                QObject::connect(d._reply, &EnginioReply::finished, finishedRequest);
                EnginioReply *ereply = d._model->removeNow(row, d._object, id);
                d.swapNetworkReply(ereply);
            }
        }
    };

    EnginioReply *remove(int row)
    {
        QJsonObject oldObject = _data.at(row).toObject();
        QString id = oldObject[EnginioString::id].toString();
        if (id.isEmpty())
            return removeDelayed(row, oldObject);
        return removeNow(row, oldObject, id);
    }

    EnginioReply *removeDelayed(int row, const QJsonObject &oldObject)
    {
        // We are about to remove a not synced new item. The item do not have id yet,
        // so we can not make a request now, we need to wait for finished signal.
        EnginioReply *ereply, *createReply;
        QString tmpId;
        Q_ASSERT(oldObject[EnginioString::id].toString().isEmpty());
        delayedOperation(row, &ereply, &tmpId, &createReply);
        SwapNetworkReplyForRemove swapNetworkReply = {{ereply, this, oldObject, tmpId}};
        QObject::connect(createReply, &EnginioReply::finished, swapNetworkReply);
        return ereply;
    }

    EnginioReply *removeNow(int row, const QJsonObject &oldObject, const QString &id)
    {
        Q_ASSERT(!id.isEmpty());
        _attachedData.ref(id, row); // TODO if refcount is > 1 then do not emit dataChanged
        EnginioReply *ereply = _enginio->remove(oldObject, _operation);
        FinishedRemoveRequest finishedRequest = { this, id };
        QObject::connect(ereply, &EnginioReply::finished, finishedRequest);
        _attachedData.insertRequestId(ereply->requestId(), row);
        QVector<int> roles(1);
        roles.append(EnginioModel::SyncedRole);
        emit q->dataChanged(q->index(row), q->index(row) , roles);
        return ereply;
    }

    EnginioReply *setValue(int row, const QString &role, const QVariant &value)
    {
        int key = _roles.key(role, EnginioModel::InvalidRole);
        return setData(row, value, key);
    }

    void setQuery(const QJsonObject &query)
    {
        _query = query;

        if (_query.contains(EnginioString::pageSize)) {
            const int pageSize = _query[EnginioString::pageSize].toDouble();
            const QString limitString(EnginioString::limit);
            const QString offsetString(EnginioString::offset);
            const unsigned limit = _query[limitString].toDouble();
            const unsigned offset = _query[offsetString].toDouble();
            if (limit)
                qWarning() << "EnginioModel::setQuery()" << "'limit' parameter can not be used together with model pagining feature, the value will be ignored";

            if (offset) {
                qWarning() << "EnginioModel::setQuery()" << "'offset' parameter can not be used together with model pagining feature, the value will be ignored";
                _query.remove(offsetString);
            }
            _query[limitString] = pageSize;
            _canFetchMore = true;
        } else {
            _canFetchMore = false;
        }
        emit q->queryChanged(query);
    }

    EnginioClient::Operation operation() const Q_REQUIRED_RESULT
    {
        return _operation;
    }

    void setOperation(const int operation)
    {
        Q_ASSERT_X(operation >= EnginioClient::ObjectOperation, "setOperation", "Invalid operation specified.");
        _operation = static_cast<EnginioClient::Operation>(operation);
        emit q->operationChanged(_operation);
    }

    void execute()
    {
        if (!_enginio || _enginio->backendId().isEmpty() || _enginio->backendSecret().isEmpty())
            return;
        if (!_query.isEmpty()) {
            // setup notifications
            QJsonObject filter;
            QJsonObject objectType;
            objectType.insert(EnginioString::objectType, _query[EnginioString::objectType]);
            filter.insert(EnginioString::data, objectType);
            _notifications.connectToBackend(this, _enginio, filter);

            // send full query
            const EnginioReply *ereply = _enginio->query(_query, _operation);
            if (_canFetchMore)
                _latestRequestedOffset = _query[EnginioString::limit].toDouble();
            FinishedFullQueryRequest finshedRequest = { this };
            QObject::connect(ereply, &EnginioReply::finished, finshedRequest);
            QObject::connect(ereply, &EnginioReply::finished, ereply, &EnginioReply::deleteLater);
        }
    }

    void finishedIncrementalUpdateRequest(const EnginioReply *reply, const QJsonObject &query)
    {
        Q_ASSERT(_canFetchMore);
        QJsonArray data(reply->data()[EnginioString::results].toArray());
        int offset = query[EnginioString::offset].toDouble();
        int limit = query[EnginioString::limit].toDouble();
        int dataCount = data.count();

        int startingOffset = qMax(offset, _data.count());

        q->beginInsertRows(QModelIndex(), startingOffset, startingOffset + dataCount -1);
        for (int i = 0; i < dataCount; ++i) {
            _data.append(data[i]);
        }

        _canFetchMore = limit <= dataCount;
        q->endInsertRows();
    }

    void finishedFullQueryRequest(const EnginioReply *reply)
    {
        q->beginResetModel();
        _data = reply->data()[EnginioString::results].toArray();
        _attachedData.initFromArray(_data);
        syncRoles();
        _canFetchMore = _canFetchMore && _data.count() && (_query[EnginioString::limit].toDouble() <= _data.count());
        q->endResetModel();
    }

    void finishedCreateRequest(const EnginioReply *reply, const QString &tmpId)
    {
        AttachedData &data = _attachedData.deref(tmpId);

        if (_attachedData.markRequestIdAsHandled(reply->requestId()))
            return; // request was handled

        int row = data.row;
        if (reply->networkError() != QNetworkReply::NoError) {
            // We tried to create something and we failed, we need to remove tmp
            // item

            // TODO add a signal here so a developer can ask an user for a conflict
            // resolution.
            receivedRemoveNotification(_data[row].toObject(), row);
            return;
        }

        const QJsonObject object = reply->data();
        receivedUpdateNotification(object, tmpId, row);
    }

    void finishedRemoveRequest(const EnginioReply *response, const QString &id)
    {
        AttachedData &data = _attachedData.deref(id);

        if (_attachedData.markRequestIdAsHandled(response->requestId()))
            return; // request was handled

        int row = data.row;
        if (row == DeletedRow || (response->networkError() != QNetworkReply::NoError && response->backendStatus() != 404)) {
            if (!data.ref) {
                // The item was not removed, because of an error. We assume that the
                // item is in sync
                emit q->dataChanged(q->index(row), q->index(row));
            }
            return;
        }
        receivedRemoveNotification(_data[row].toObject(), row);
    }

    void finishedUpdateRequest(const EnginioReply *reply, const QString &id, const QJsonObject &oldValue)
    {
        AttachedData &data = _attachedData.deref(id);

        if (_attachedData.markRequestIdAsHandled(reply->requestId()))
            return; // request was handled

        int row = data.row;
        if (row == DeletedRow) {
            // We tried to update something that we already deleted
            // everything should be handled
            return;
        }
        if (reply->networkError() != QNetworkReply::NoError) {
            if (reply->backendStatus() == 404) {
                // We tried to update something that got deleted in between, probably on
                // the server side. Changing operation type to remove, so the cache
                // can be in sync with the server again.

                // TODO add a signal here so a developer can ask an user for a conflict
                // resolution.
                receivedRemoveNotification(_data[row].toObject(), row);
            } else {
                // Try to rollback the change.
                // TODO it is not perfect https://github.com/enginio/enginio-qt/issues/200
                _data.replace(row, oldValue);
                emit q->dataChanged(q->index(row), q->index(row));
            }
            return;
        }
        receivedUpdateNotification(reply->data(), id, row);
    }

    struct SwapNetworkReplyForSetData
    {
        SwapNetworkReplyBase d;
        QVariant _value;
        int _role;

        void operator ()(EnginioReply *finishedCreateReply)
        {
            if (finishedCreateReply->isError()) {
                d.markAsError(QByteArrayLiteral("Dependent create query failed, so object coudl not be updated"));
            } else {
                const int row = d.getCurrentRow();
                QString id = d.getAndSetCurrentId(finishedCreateReply);
                FinishedUpdateRequest finished = { d._model, id, d._object };
                QObject::connect(d._reply, &EnginioReply::finished, finished);
                EnginioReply *ereply = d._model->setDataNow(row, _value, _role, d._object, id);
                d.swapNetworkReply(ereply);
            }
        }
    };

    EnginioReply *setData(const int row, const QVariant &value, int role)
    {
        if (role > EnginioModel::SyncedRole) {
            QJsonObject oldObject = _data.at(row).toObject();
            QString id = oldObject[EnginioString::id].toString();
            if (id.isEmpty())
                return setDataDelyed(row, value, role, oldObject);
            return setDataNow(row, value, role, oldObject, id);
        }
        EnginioClientPrivate *client = EnginioClientPrivate::get(_enginio);
        QNetworkReply *nreply = new EnginioFakeReply(client, constructErrorMessage(QByteArrayLiteral("EnginioModel: Trying to update an object with unknown role")));
        EnginioReply *ereply = new EnginioReply(client, nreply);
        return ereply;
    }

    void delayedOperation(int row, EnginioReply **newReply, QString *tmpId, EnginioReply **createReply)
    {
        Q_ASSERT(!_attachedData.isSynced(row));
        AttachedData data = _attachedData.ref(row);
        *createReply = data.createReply;
        Q_ASSERT(*createReply);
        *tmpId = data.id;
        Q_ASSERT(tmpId->startsWith('t'));
        EnginioClientPrivate *client = EnginioClientPrivate::get(_enginio);
        EnginioDummyReply *nreply = new EnginioDummyReply(*createReply);
        *newReply = new EnginioReply(client, nreply);
    }

    EnginioReply *setDataDelyed(int row, const QVariant &value, int role, const QJsonObject &oldObject)
    {
        // We are about to update a not synced new item. The item do not have id yet,
        // so we can not make a request now, we need to wait for finished signal.
        Q_ASSERT(role > EnginioModel::SyncedRole);
        EnginioReply *ereply, *createReply;
        QString tmpId;
        Q_ASSERT(oldObject[EnginioString::id].toString().isEmpty());
        delayedOperation(row, &ereply, &tmpId, &createReply);
        SwapNetworkReplyForSetData swapNetworkReply = {{ereply, this, oldObject, tmpId}, value, role};
        QObject::connect(createReply, &EnginioReply::finished, swapNetworkReply);
        return ereply;
    }

    EnginioReply *setDataNow(const int row, const QVariant &value, int role, const QJsonObject &oldObject, const QString &id)
    {
        Q_ASSERT(!id.isEmpty());
        Q_ASSERT(role > EnginioModel::SyncedRole);
        const QString roleName(_roles.value(role));
        QJsonObject deltaObject;
        QJsonObject newObject = oldObject;
        deltaObject[roleName] = newObject[roleName] = QJsonValue::fromVariant(value);
        deltaObject[EnginioString::id] = id;
        deltaObject[EnginioString::objectType] = newObject[EnginioString::objectType];
        EnginioReply *ereply = _enginio->update(deltaObject, _operation);
        FinishedUpdateRequest finished = { this, id, oldObject };
        QObject::connect(ereply, &EnginioReply::finished, finished);
        _attachedData.ref(id, row);
        _data.replace(row, newObject);
        _attachedData.insertRequestId(ereply->requestId(), row);
        emit q->dataChanged(q->index(row), q->index(row));
        return ereply;
    }

    void syncRoles()
    {
        QJsonObject firstObject(_data.first().toObject()); // TODO it expects certain data structure in all objects, add way to specify roles

        if (!_roles.count()) {
            _roles.reserve(firstObject.count());
            _roles[EnginioModel::SyncedRole] = EnginioString::_synced; // TODO Use a proper name, can we make it an attached property in qml? Does it make sense to try?
            _roles[EnginioModel::CreatedAtRole] = EnginioString::createdAt;
            _roles[EnginioModel::UpdatedAtRole] = EnginioString::updatedAt;
            _roles[EnginioModel::IdRole] = EnginioString::id;
            _roles[EnginioModel::ObjectTypeRole] = EnginioString::objectType;
            _rolesCounter = EnginioModel::LastRole;
        }

        // estimate additional dynamic roles:
        QSet<QString> definedRoles = _roles.values().toSet();
        for (QJsonObject::const_iterator i = firstObject.constBegin(); i != firstObject.constEnd(); ++i) {
            const QString key = i.key();
            if (definedRoles.contains(key)) {
                // we skip predefined keys so we can keep constant id for them
                if (Q_UNLIKELY(key == EnginioString::_synced))
                    qWarning("EnginioModel can not be used with objects having \"_synced\" property. The property will be overriden.");
            } else
                _roles[_rolesCounter++] = i.key();
        }
    }

    QHash<int, QByteArray> roleNames() const Q_REQUIRED_RESULT
    {
        // TODO this is not optimal, but happen once, do we want to do something about it?
        QHash<int, QByteArray> roles;
        roles.reserve(_roles.count());
        for (QHash<int, QString>::const_iterator i = _roles.constBegin();
             i != _roles.constEnd();
             ++i) {
            roles.insert(i.key(), i.value().toUtf8());
        }
        return roles;
    }

    int rowCount() const Q_REQUIRED_RESULT
    {
        return _data.count();
    }

    QVariant data(unsigned row, int role) Q_REQUIRED_RESULT
    {
        if (role == EnginioModel::SyncedRole) {
            return _attachedData.isSynced(row);
        }

        if (role == Qt::DisplayRole)
            return _data.at(row);

        const QJsonObject object = _data.at(row).toObject();
        if (!object.isEmpty()) {
            const QString roleName = _roles.value(role);
            if (!roleName.isEmpty())
                return object[roleName];
        }

        return QVariant();
    }

    bool canFetchMore() const Q_REQUIRED_RESULT
    {
        return _canFetchMore;
    }

    void fetchMore(int row)
    {
        int currentOffset = _data.count();
        if (!_canFetchMore || currentOffset < _latestRequestedOffset)
            return; // we do not want to spam the server, lets wait for the last fetch

        QJsonObject query(_query);

        int limit = query[EnginioString::limit].toDouble();
        limit = qMax(row - currentOffset, limit); // check if default limit is not too small

        query[EnginioString::offset] = currentOffset;
        query[EnginioString::limit] = limit;

        qDebug() << Q_FUNC_INFO << query;
        _latestRequestedOffset += limit;
        EnginioReply *ereply = _enginio->query(query, _operation);
        QObject::connect(ereply, &EnginioReply::finished, ereply, &EnginioReply::deleteLater);
        FinishedIncrementalUpdateRequest finishedRequest = { this, query };
        QObject::connect(ereply, &EnginioReply::finished, finishedRequest);
    }
};

const int EnginioModelPrivate::IncrementalModelUpdate = -2;


/*!
  \class EnginioModel
  \inmodule enginio-qt
  \ingroup enginio-client
  \target EnginioModelCpp
  \brief EnginioModel represents data from Enginio as a \l QAbstractListModel.

  Example of setting a query.

  The query has to result in a list.

  Inside the delegate you have the magic properties model and index.
  Exposes the data as "model".
  index

  Sorting is done server side, as soon as data is changed locally it will be invalid.

  \note that the EnginioClient does emit the finished and error signals for the model.

  For the QML version of this class see \l {Enginio1::EnginioModel}{EnginioModel (QML)}
*/

/*!
    Constructs a new model with \a parent as QObject parent.
*/
EnginioModel::EnginioModel(QObject *parent)
    : QAbstractListModel(parent)
    , d(new EnginioModelPrivate(this))
{}

/*!
    Destroys the model.
*/
EnginioModel::~EnginioModel()
{}

/*!
  \enum EnginioModel::Roles

  EnginioModel defines roles which represent data used by every object
  stored in the Enginio backend

  \value CreatedAtRole \c When an item was created
  \value UpdatedAtRole \c When an item was updated last time
  \value IdRole \c What is the id of an item
  \value ObjectTypeRole \c What is item type
  \value SyncedRole \c Mark if an item is in sync with the backend
  \omitvalue InvalidRole
  \omitvalue LastRole

  Additionally EnginioModel supports dynamic roles which are mapped
  directly from recieved data. EnginioModel is mapping first item properties
  to role names.

  \note Some objects may not contain value for a static role, it may happen
  for example when an item is not in sync with the backend.

  \sa EnginioModel::roleNames()
*/

/*!
  \property EnginioModel::enginio
  \brief The EnginioClient used by the model.

  \sa EnginioClient
*/
EnginioClient *EnginioModel::enginio() const
{
    return d->enginio();
}

void EnginioModel::setEnginio(const EnginioClient *enginio)
{
    if (enginio == d->enginio())
        return;
    d->setEnginio(enginio);
}

/*!
  \property EnginioModel::query
  \brief The query which returns the data for the model.

  Sorting preserved until insertion/deletion

  \sa EnginioClient::query()
*/
QJsonObject EnginioModel::query()
{
    return d->query();
}

void EnginioModel::setQuery(const QJsonObject &query)
{
    if (d->query() == query)
        return;
    return d->setQuery(query);
}

/*!
  \property EnginioModel::operation
  \brief The operation type of the query
  \sa EnginioClient::Operation, query()
  \return returns the Operation
*/
EnginioClient::Operation EnginioModel::operation() const
{
    return d->operation();
}

void EnginioModel::setOperation(EnginioClient::Operation operation)
{
    if (operation == d->operation())
        return;
    d->setOperation(operation);
}

/*!
  Append \a value to this model local cache and send a create request
  to enginio backend.
  \return reply from backend
  \sa EnginioClient::create()
*/
EnginioReply *EnginioModel::append(const QJsonObject &value)
{
    if (Q_UNLIKELY(!d->enginio())) {
        qWarning("EnginioModel::append(): Enginio client is not set");
        return 0;
    }

    return d->append(value);
}

/*!
  Remove a value from \a row in this model local cache and send
  a remove request to enginio backend.
  \return reply from backend
  \sa EnginioClient::remove()
*/
EnginioReply *EnginioModel::remove(int row)
{
    if (Q_UNLIKELY(!d->enginio())) {
        qWarning("EnginioModel::remove(): Enginio client is not set");
        return 0;
    }

    if (unsigned(row) >= unsigned(d->rowCount())) {
        EnginioClientPrivate *client = EnginioClientPrivate::get(d->enginio());
        QNetworkReply *nreply = new EnginioFakeReply(client, constructErrorMessage(QByteArrayLiteral("EnginioModel::remove: row is out of range")));
        EnginioReply *ereply = new EnginioReply(client, nreply);
        return ereply;
    }

    return d->remove(row);
}

/*!
  Update a value on \a row of this model's local cache
  and send an update request to the Enginio backend.

  The \a role is the property of the object that will be updated to be the new \a value.

  \return reply from backend
  \sa EnginioClient::update()
*/
EnginioReply *EnginioModel::setProperty(int row, const QString &role, const QVariant &value)
{
    if (Q_UNLIKELY(!d->enginio())) {
        qWarning("EnginioModel::setProperty(): Enginio client is not set");
        return 0;
    }

    if (unsigned(row) >= unsigned(d->rowCount())) {  // TODO remove as soon as we have a sparse array.
        EnginioClientPrivate *client = EnginioClientPrivate::get(d->enginio());
        QNetworkReply *nreply = new EnginioFakeReply(client, constructErrorMessage(QByteArrayLiteral("EnginioModel::setProperty: row is out of range")));
        EnginioReply *ereply = new EnginioReply(client, nreply);
        return ereply;
    }

    return d->setValue(row, role, value);
}

/*!
    \overload
    \internal
*/
Qt::ItemFlags EnginioModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

/*!
    \overload
    Use this function to access the model data at \a index.
    With the \l roleNames() function the mapping of JSON property names to data roles used as \a role is available.
    The data returned will be JSON (for example a string for simple objects, or a JSON Object).
*/
QVariant EnginioModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= d->rowCount())
        return QVariant();

    return d->data(index.row(), role);
}

/*!
    \overload
    \internal
*/
int EnginioModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return d->rowCount();
}

/*!
    \overload
    \internal
*/
bool EnginioModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() >= d->rowCount()) // TODO remove as soon as we have a sparse array.
        return false;

    return d->setData(index.row(), value, role);
}

/*!
    \overload
    Returns the mapping of the model's roles to names.
    EnginioModel will assign the properties of the objects in the \l query()
    to roles (greater than \l Qt::UserRole).
    Use this function to map the object property names to the role integers.
*/
QHash<int, QByteArray> EnginioModel::roleNames() const
{
    return d->roleNames();
}

/*!
    \internal
    Allows to disable notifications for autotests.
*/
void EnginioModel::disableNotifications()
{
    d->disableNotifications();
}

/*!
    \overload
    \internal
*/
void EnginioModel::fetchMore(const QModelIndex &parent)
{
    d->fetchMore(parent.row());
}

/*!
    \overload
    \internal
*/
bool EnginioModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return d->canFetchMore();
}
