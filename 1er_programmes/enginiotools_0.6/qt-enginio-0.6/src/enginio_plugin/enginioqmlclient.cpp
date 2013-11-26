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

#include "enginioqmlclient.h"
#include "Enginio/private/enginioclient_p.h"
#include "enginioqmlobjectadaptor_p.h"

#include <QtQml/qjsvalue.h>

#include <QDebug>

/*!
  \qmltype Enginio
  \instantiates EnginioQmlClient
  \inqmlmodule Enginio 1
  \ingroup engino-qml

  \brief client interface to access Enginio
  \snippet simple.qml import

  Enginio is the heart of the QML API for Enginio.
  It is used for all communication with the Enginio backend.
  \l EnginioModel compliments it to make handling of multiple objects simple.

  The backend is identified by \l{backendId}{backend ID} and \l{backendSecret}{secret}.
  \snippet simple.qml client

  Once the backend is configured, it is possible to run queries by calling query on
  Enginio.
  For example to get all objects stored with the type "objects.image" run this query:
  \snippet simple.qml client-query

  Enginio gives you a convenient way to handle the responses to your queryies as well:
  \snippet simple.qml client-signals
*/

/*!
  \qmlproperty string Enginio1::Enginio::backendId
  Enginio backend ID. This can be obtained from the Enginio dashboard.
*/

/*!
  \qmlproperty string Enginio1::Enginio::backendSecret
  Enginio backend secret. This can be obtained from the Enginio dashboard.
*/

/*!
  \qmlproperty url Enginio1::Enginio::serviceUrl
  \internal
  Enginio backend URL.

  Usually there is no need to change the default URL.
*/

/*!
  \qmlmethod EnginioReply Enginio1::Enginio::search(QJsonObject query)
  \brief Perform a full text search on the database
*/

/*!
  \qmlmethod EnginioReply Enginio1::Enginio::query(QJsonObject query, Operation operation)
  \brief Query the database.
*/
/*!
  \qmlmethod EnginioReply Enginio1::Enginio::create(QJsonObject query, Operation operation)
  \brief Create an object in the database.
*/
/*!
  \qmlmethod EnginioReply Enginio1::Enginio::update(QJsonObject query, Operation operation)
  \brief Update an object in the database.
*/
/*!
  \qmlmethod EnginioReply Enginio1::Enginio::remove(QJsonObject query, Operation operation)
  \brief Remove an object from the database.
*/

/*!
  \qmlmethod EnginioReply Enginio1::Enginio::uploadFile(QJsonObject object, QUrl file)
  \brief Stores a \a file attached to an \a object in Enginio

  Each uploaded file needs to be associated with an object in the database.
  \note The upload will only work with the propper server setup: in the dashboard create a property
  of the type that you will use. Set this property to be a reference to files.

  In order to upload a file, first create an object:
  \snippet qmltests/tst_files.qml upload-create-object

  Then do the actual upload:
  \snippet qmltests/tst_files.qml upload

  Note: There is no need to directly delete files.
  Instead when the object that contains the link to the file gets deleted,
  the file will automatically be deleted as well.

  \sa downloadFile()
*/

/*!
  \qmlmethod EnginioReply Enginio1::Enginio::downloadFile(QJsonObject object)
  \brief Get the download URL for a file

  \snippet qmltests/tst_files.qml download

  The response contains the download URL and the duration how long the URL will be valid.
  \code
    downloadReply.data.expiringUrl
    downloadReply.data.expiresAt
  \endcode

  \sa uploadFile()
*/

/*!
  \qmlsignal Enginio1::Enginio::finished(EnginioReply reply)
  This signal is emitted when a \a reply finishes.

  \note that this signal is alwasy emitted, independent of whether
  the reply finished successfully or not.
*/

/*!
  \qmlsignal Enginio1::Enginio::error(EnginioReply reply)
  This signal is emitted when a \a reply finishes and contains an error.
*/

EnginioQmlClient::EnginioQmlClient(QObject *parent)
    : EnginioClient(parent, new EnginioQmlClientPrivate(this))
{
    Q_D(EnginioQmlClient);
    d->init();
}

void EnginioQmlClientPrivate::init()
{
    EnginioClientPrivate::init();
    qRegisterMetaType<EnginioQmlClient*>();
    qRegisterMetaType<EnginioQmlReply*>();
}

EnginioQmlReply *EnginioQmlClient::query(const QJSValue &query, const Operation operation)
{
    Q_D(EnginioQmlClient);

    d->setEngine(query);
    ObjectAdaptor<QJSValue> o(query, d);
    QNetworkReply *nreply = d_ptr->query<QJSValue>(o, static_cast<EnginioClientPrivate::Operation>(operation));
    EnginioQmlReply *ereply = new EnginioQmlReply(d, nreply);
    return ereply;
}

EnginioQmlReply *EnginioQmlClient::create(const QJSValue &object, const Operation operation)
{
    Q_D(EnginioQmlClient);

    if (!object.isObject())
        return 0;

    d->setEngine(object);
    ObjectAdaptor<QJSValue> o(object, d);
    QNetworkReply *nreply = d_ptr->create<QJSValue>(o, operation);
    EnginioQmlReply *ereply = new EnginioQmlReply(d, nreply);

    return ereply;
}

EnginioQmlReply *EnginioQmlClient::update(const QJSValue &object, const Operation operation)
{
    Q_D(EnginioQmlClient);

    if (!object.isObject())
        return 0;

    d->setEngine(object);
    ObjectAdaptor<QJSValue> o(object, d);
    QNetworkReply *nreply = d_ptr->update<QJSValue>(o, operation);
    EnginioQmlReply *ereply = new EnginioQmlReply(d, nreply);

    return ereply;
}

EnginioQmlReply *EnginioQmlClient::remove(const QJSValue &object, const Operation operation)
{
    Q_D(EnginioQmlClient);

    if (!object.isObject())
        return 0;

    d->setEngine(object);
    ObjectAdaptor<QJSValue> o(object, d);
    QNetworkReply *nreply = d_ptr->remove<QJSValue>(o, operation);
    EnginioQmlReply *ereply = new EnginioQmlReply(d, nreply);

    return ereply;
}

EnginioQmlReply *EnginioQmlClient::downloadFile(const QJSValue &object)
{
    Q_D(EnginioQmlClient);

    if (!object.isObject())
        return 0;

    d->setEngine(object);
    ObjectAdaptor<QJSValue> o(object, d);
    QNetworkReply *nreply = d_ptr->downloadFile<QJSValue>(o);
    EnginioQmlReply *ereply = new EnginioQmlReply(d, nreply);

    return ereply;
}

EnginioQmlReply *EnginioQmlClient::uploadFile(const QJSValue &object, const QUrl &url)
{
    Q_D(EnginioQmlClient);

    if (!object.isObject())
        return 0;

    d->setEngine(object);
    ObjectAdaptor<QJSValue> o(object, d);
    QNetworkReply *nreply = d_ptr->uploadFile<QJSValue>(o, url);
    EnginioQmlReply *ereply = new EnginioQmlReply(d, nreply);

    return ereply;
}

QByteArray EnginioQmlClientPrivate::toJson(const QJSValue &value)
{
    if (!_stringify.isCallable())
        Q_UNIMPLEMENTED(); // TODO maybe _value.toString().toUtf8()?
    return _stringify.call(QJSValueList() << value).toString().toUtf8();
}

QJSValue EnginioQmlClientPrivate::fromJson(const QByteArray &value)
{
    if (!_parse.isCallable())
        Q_UNIMPLEMENTED();
    return _parse.call(QJSValueList() << _engine->toScriptValue(value));
}

void EnginioQmlClientPrivate::_setEngine(QJSEngine *engine)
{
    Q_ASSERT(!_engine);
    if (engine) {
        _engine = engine;
        _stringify = engine->evaluate("JSON.stringify");
        _parse = engine->evaluate("JSON.parse");
        Q_ASSERT(_stringify.isCallable());
    }
}

