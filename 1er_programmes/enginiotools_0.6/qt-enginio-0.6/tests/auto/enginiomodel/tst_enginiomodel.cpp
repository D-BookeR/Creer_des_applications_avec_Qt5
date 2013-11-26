/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
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
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QtTest>
#include <QtCore/qobject.h>
#include <QtCore/qthread.h>

#include <QtWidgets/qlistview.h>
#include <QtWidgets/qapplication.h>

#include <Enginio/enginioclient.h>
#include <Enginio/enginioreply.h>
#include <Enginio/enginiomodel.h>
#include <Enginio/enginioidentity.h>

#include "../common/common.h"

class tst_EnginioModel: public QObject
{
    Q_OBJECT

    QString _backendName;
    EnginioTests::EnginioBackendManager _backendManager;
    QByteArray _backendId;
    QByteArray _backendSecret;

public slots:
    void error(EnginioReply *reply) {
        qDebug() << "\n\n### ERROR";
        qDebug() << reply->errorString();
        reply->dumpDebugInfo();
        qDebug() << "\n###\n";
    }

private slots:
    void initTestCase();
    void cleanupTestCase();
    void ctor();
    void enginio_property();
    void query_property();
    void operation_property();
    void roleNames();
    void listView();
    void invalidRemove();
    void invalidSetProperty();
    void multpleConnections();
    void deletionReordered();
    void deleteTwiceTheSame();
    void updateAndDeleteReordered();
    void updateReordered();
    void append();
    void removeExternallyRemovedObject();
    void setPropertyOnExternallyRemovedObject();
    void createAndModify();
    void externalNotification();
    void createUpdateRemoveWithNotification();
private:
    template<class T>
    void externallyRemovedImpl();
};

void tst_EnginioModel::initTestCase()
{
    if (EnginioTests::TESTAPP_URL.isEmpty())
        QFAIL("Needed environment variable ENGINIO_API_URL is not set!");

    _backendName = QStringLiteral("EnginioClient") + QString::number(QDateTime::currentMSecsSinceEpoch());
    QVERIFY(_backendManager.createBackend(_backendName));

    QJsonObject apiKeys = _backendManager.backendApiKeys(_backendName, EnginioTests::TESTAPP_ENV);
    _backendId = apiKeys["backendId"].toString().toUtf8();
    _backendSecret = apiKeys["backendSecret"].toString().toUtf8();

    QVERIFY(!_backendId.isEmpty());
    QVERIFY(!_backendSecret.isEmpty());

    // The test operates on user data.
    EnginioTests::prepareTestUsersAndUserGroups(_backendId, _backendSecret);
    EnginioTests::prepareTestObjectType(_backendName);
}

void tst_EnginioModel::cleanupTestCase()
{
    QVERIFY(_backendManager.removeBackend(_backendName));
}

void tst_EnginioModel::ctor()
{
    {
        EnginioModel model1, model2(this);
        Q_UNUSED(model1);
        Q_UNUSED(model2);
    }

    QJsonObject query = QJsonDocument::fromJson("{\"foo\":\"invalid\"}").object();
    QVERIFY(!query.isEmpty());
    {   // check if destructor of a fully initilized EnginioClient detach fully initilized model
        EnginioModel model;
        model.setOperation(EnginioClient::ObjectOperation);
        model.setQuery(query);

        EnginioClient client;
        QObject::connect(&client, SIGNAL(error(EnginioReply *)), this, SLOT(error(EnginioReply *)));
        client.setBackendId(_backendId);
        client.setServiceUrl(EnginioTests::TESTAPP_URL);
        client.setBackendSecret(_backendSecret);
        model.setEnginio(&client);
    }
    {   // check if destructor of a fully initilized EnginioClient detach fully initilized model
        EnginioClient client;
        QObject::connect(&client, SIGNAL(error(EnginioReply *)), this, SLOT(error(EnginioReply *)));
        EnginioModel model;
        model.setOperation(EnginioClient::ObjectOperation);
        model.setQuery(query);
        client.setBackendId(_backendId);
        client.setServiceUrl(EnginioTests::TESTAPP_URL);
        client.setBackendSecret(_backendSecret);
        model.setEnginio(&client);
    }
}

void tst_EnginioModel::enginio_property()
{
    {
        EnginioClient client;
        QObject::connect(&client, SIGNAL(error(EnginioReply *)), this, SLOT(error(EnginioReply *)));
        EnginioModel model;
        // No initial value
        QCOMPARE(model.enginio(), static_cast<EnginioClient*>(0));

        QSignalSpy spy(&model, SIGNAL(enginioChanged(EnginioClient*)));
        model.setEnginio(&client);
        QCOMPARE(model.enginio(), &client);
        QTRY_COMPARE(spy.count(), 1);
    }
    {
        EnginioModel model;
        QSignalSpy spy(&model, SIGNAL(enginioChanged(EnginioClient*)));
        {
            EnginioClient client;
            QObject::connect(&client, SIGNAL(error(EnginioReply *)), this, SLOT(error(EnginioReply *)));
            model.setEnginio(&client);
            QCOMPARE(model.enginio(), &client);
            QTRY_COMPARE(spy.count(), 1);
            QCOMPARE(spy[0][0].value<EnginioClient*>(), &client);
        }
        QCOMPARE(model.enginio(), static_cast<EnginioClient*>(0));
        QTRY_COMPARE(spy.count(), 2);
        QCOMPARE(spy[1][0].value<EnginioClient*>(), static_cast<EnginioClient*>(0));
    }
    {
        EnginioModel model;
        QTest::ignoreMessage(QtWarningMsg, "EnginioModel::append(): Enginio client is not set");
        QVERIFY(!model.append(QJsonObject()));
        QTest::ignoreMessage(QtWarningMsg, "EnginioModel::remove(): Enginio client is not set");
        QVERIFY(!model.remove(0));
        QTest::ignoreMessage(QtWarningMsg, "EnginioModel::setProperty(): Enginio client is not set");
        QVERIFY(!model.setProperty(0, "blah", QVariant()));
    }
    {
        // check if initial set is not calling reset twice
        EnginioClient client;
        client.setBackendId(_backendId);
        client.setBackendSecret(_backendSecret);
        client.setServiceUrl(EnginioTests::TESTAPP_URL);

        EnginioModel model;
        QSignalSpy spyAboutToReset(&model, SIGNAL(modelAboutToBeReset()));
        QSignalSpy spyReset(&model, SIGNAL(modelReset()));
        QJsonObject query;
        query.insert("limit", 1);
        model.setQuery(query);
        model.setOperation(EnginioClient::UserOperation);
        model.setEnginio(&client);

        QTRY_COMPARE(spyAboutToReset.count(), 1);
        QTRY_COMPARE(spyReset.count(), 1);
    }
}

void tst_EnginioModel::query_property()
{
    QJsonObject query = QJsonDocument::fromJson("{\"foo\":\"invalid\"}").object();
    QVERIFY(!query.isEmpty());
    EnginioModel model;
    QSignalSpy spy(&model, SIGNAL(queryChanged(QJsonObject)));

    // initial value is empty
    QVERIFY(model.query().isEmpty());

    model.setQuery(query);
    QCOMPARE(model.query(), query);
    QTRY_COMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0].value<QJsonObject>(), query);

    // try to set the same query again, it should not emit the signal
    model.setQuery(query);
    QCOMPARE(model.query(), query);
    QCOMPARE(spy.count(), 1);

    model.setQuery(QJsonObject());
    QTRY_COMPARE(spy.count(), 2);
    QVERIFY(model.query().isEmpty());
    QVERIFY(spy[1][0].value<QJsonObject>().isEmpty());
}

void tst_EnginioModel::operation_property()
{
    EnginioModel model;
    QSignalSpy spy(&model, SIGNAL(operationChanged(EnginioClient::Operation)));

    // check initial value
    QCOMPARE(model.operation(), EnginioClient::ObjectOperation);

    model.setOperation(EnginioClient::UserOperation);
    QCOMPARE(model.operation(), EnginioClient::UserOperation);
    QTRY_COMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0].value<EnginioClient::Operation>(), EnginioClient::UserOperation);

    // try to set the same operation again, it should not emit the signal
    model.setOperation(EnginioClient::UserOperation);
    QCOMPARE(model.operation(), EnginioClient::UserOperation);
    QCOMPARE(spy.count(), 1);

    // try to change it agian.
    model.setOperation(EnginioClient::UsergroupOperation);
    QTRY_COMPARE(spy.count(), 2);
    QCOMPARE(model.operation(), EnginioClient::UsergroupOperation);
    QCOMPARE(spy[1][0].value<EnginioClient::Operation>(), EnginioClient::UsergroupOperation);
}

void tst_EnginioModel::roleNames()
{
    struct EnginioModelChild: public EnginioModel
    {
        using EnginioModel::roleNames;
    } model;
    QVERIFY(model.roleNames().isEmpty()); // Initilial value

    EnginioClient client;
    QObject::connect(&client, SIGNAL(error(EnginioReply *)), this, SLOT(error(EnginioReply *)));
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);
    model.setEnginio(&client);

    QVERIFY(model.enginio() == &client);

    model.setOperation(EnginioClient::UserOperation);
    QJsonObject query = QJsonDocument::fromJson("{\"limit\":5}").object();
    model.setQuery(query);

    QTRY_COMPARE(model.rowCount(), 5);
    QHash<int, QByteArray> roles = model.roleNames();
    QSet<QByteArray> expectedRoles;
    expectedRoles << "updatedAt" << "objectType" << "id" << "username" << "createdAt" << "_synced";
    QSet<QByteArray> roleNames = roles.values().toSet();
    foreach(const QByteArray role, expectedRoles)
        QVERIFY(roleNames.contains(role));
}

void tst_EnginioModel::listView()
{
    QJsonObject query = QJsonDocument::fromJson("{\"limit\":2}").object();
    QVERIFY(!query.isEmpty());
    EnginioModel model;
    model.setQuery(query);
    model.setOperation(EnginioClient::UserOperation);

    EnginioClient client;
    QObject::connect(&client, SIGNAL(error(EnginioReply *)), this, SLOT(error(EnginioReply *)));
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);
    model.setEnginio(&client);

    QListView view;
    view.setModel(&model);
    view.show();

    QTRY_COMPARE(model.rowCount(), 2);
    QVERIFY(view.model() == &model);
    QVERIFY(view.indexAt(QPoint(1,1)).data().isValid());
}

struct ReplyCounter
{
    int &counter;
    ReplyCounter(int *storage)
        : counter(*storage)
    {}

    void operator ()(EnginioReply *)
    {
        ++counter;
    }
};

struct InvalidRemoveErrorChecker: public ReplyCounter
{
    InvalidRemoveErrorChecker(int *storage)
        : ReplyCounter(storage)
    {}

    void operator ()(EnginioReply *reply)
    {
        QVERIFY(reply->isFinished());
        QVERIFY(reply->isError());
        QCOMPARE(reply->errorType(), EnginioReply::BackendError);
        QVERIFY(reply->networkError() != QNetworkReply::NoError);\
        QCOMPARE(reply->backendStatus(), 400);

        QJsonObject data = reply->data();
        QVERIFY(!data.isEmpty());

        QVERIFY(!data["errors"].toArray()[0].toObject()["message"].toString().isEmpty());
        QVERIFY(!data["errors"].toArray()[0].toObject()["reason"].toString().isEmpty());

        ReplyCounter::operator ()(reply);
    }
};
void tst_EnginioModel::invalidRemove()
{
    EnginioClient client;
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);

    EnginioModel model;
    model.setEnginio(&client);

    int counter = 0;
    InvalidRemoveErrorChecker replyCounter(&counter);
    EnginioReply *reply;

    reply = model.remove(0);
    QVERIFY(reply);
    QVERIFY(reply->parent());
    QObject::connect(reply, &EnginioReply::finished, replyCounter);

    reply = model.remove(-10);
    QVERIFY(reply);
    QVERIFY(reply->parent());
    QObject::connect(reply, &EnginioReply::finished, replyCounter);

    reply = model.remove(-1);
    QVERIFY(reply);
    QVERIFY(reply->parent());
    QObject::connect(reply, &EnginioReply::finished, replyCounter);

    reply = model.remove(model.rowCount());
    QVERIFY(reply);
    QVERIFY(reply->parent());
    QObject::connect(reply, &EnginioReply::finished, replyCounter);

    QTRY_COMPARE(counter, 4);
}

void tst_EnginioModel::invalidSetProperty()
{
    EnginioClient client;
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);

    EnginioModel model;
    model.setEnginio(&client);
    QJsonObject query = QJsonDocument::fromJson("{\"limit\":2}").object();
    model.setOperation(EnginioClient::UserOperation);
    model.setQuery(query);

    QTRY_VERIFY(model.rowCount());

    int counter = 0;
    ReplyCounter replyCounter(&counter);
    EnginioReply *reply;

    reply = model.setProperty(-10, "Blah", QVariant(123));
    QVERIFY(reply);
    QVERIFY(reply->parent());
    QObject::connect(reply, &EnginioReply::finished, replyCounter);

    reply = model.setProperty(-1, "Blah", QVariant(123));
    QVERIFY(reply);
    QVERIFY(reply->parent());
    QObject::connect(reply, &EnginioReply::finished, replyCounter);

    reply = model.setProperty(model.rowCount(), "Blah", QVariant(123));
    QVERIFY(reply);
    QVERIFY(reply->parent());
    QObject::connect(reply, &EnginioReply::finished, replyCounter);

    reply = model.setProperty(0, "Blah", QVariant(123)); // invalid Role
    QVERIFY(reply);
    QVERIFY(reply->parent());
    QObject::connect(reply, &EnginioReply::finished, replyCounter);

    QTRY_COMPARE(counter, 4);
}

struct EnginioClientConnectionSpy: public EnginioClient
{
    virtual void connectNotify(const QMetaMethod &signal) Q_DECL_OVERRIDE
    {
        counter[signal.name()] += 1;
    }
    virtual void disconnectNotify(const QMetaMethod &signal) Q_DECL_OVERRIDE
    {
        counter[signal.name()] -= 1;
    }

    QHash<QByteArray, int> counter;
};

struct EnginioModelConnectionSpy: public EnginioModel
{
    virtual void connectNotify(const QMetaMethod &signal) Q_DECL_OVERRIDE
    {
        counter[signal.name()] += 1;
    }
    virtual void disconnectNotify(const QMetaMethod &signal) Q_DECL_OVERRIDE
    {
        counter[signal.name()] -= 1;
    }

    QHash<QByteArray, int> counter;
};

void tst_EnginioModel::multpleConnections()
{
    {
        EnginioClientConnectionSpy client1;
        client1.setBackendId(_backendId);
        client1.setBackendSecret(_backendSecret);
        client1.setServiceUrl(EnginioTests::TESTAPP_URL);
        EnginioClientConnectionSpy client2;
        client2.setBackendId(_backendId);
        client2.setBackendSecret(_backendSecret);
        client2.setServiceUrl(EnginioTests::TESTAPP_URL);

        EnginioModelConnectionSpy model;
        for (int i = 0; i < 20; ++i) {
            model.setEnginio(&client1);
            model.setEnginio(&client2);
            model.setEnginio(0);
        }

        // The values here are not strict. Use qDebug() << model.counter; to see what
        // makes sense. Just to be sure 2097150 or 20 doesn't.
        QCOMPARE(model.counter["operationChanged"], 0);
        QCOMPARE(model.counter["queryChanged"], 0);
        QCOMPARE(model.counter["enginioChanged"], 0);
        QCOMPARE(client1.counter["finished"], 0);
        QCOMPARE(client2.counter["finished"], 0);

        // All of them are acctually disconnected but disconnectNotify is not called, it is
        // a known bug in Qt.
        QCOMPARE(client1.counter["backendIdChanged"], 20);
        QCOMPARE(client1.counter["backendSecretChanged"], 20);
        QCOMPARE(client1.counter["destroyed"], 20);
        QCOMPARE(client2.counter["backendIdChanged"], 20);
        QCOMPARE(client2.counter["backendSecretChanged"], 20);
        QCOMPARE(client2.counter["destroyed"], 20);
    }
    {
        EnginioClientConnectionSpy client;
        client.setBackendId(_backendId);
        client.setBackendSecret(_backendSecret);
        client.setServiceUrl(EnginioTests::TESTAPP_URL);

        EnginioModelConnectionSpy model;
        model.setEnginio(&client);
        QJsonObject query1, query2;
        query1.insert("objectType", QString("objects.todos"));
        query2.insert("objectType", QString("objects.blah"));
        for (int i = 0; i < 20; ++i) {
            model.setQuery(query1);
            model.setQuery(query2);
            model.setQuery(QJsonObject());
        }

        // The values here are not strict. Use qDebug() << model.counter; to see what
        // makes sense. Just to be sure 2097150 or 20 doesn't.
        QCOMPARE(model.counter["operationChanged"], 0);
        QCOMPARE(model.counter["queryChanged"], 0);
        QCOMPARE(model.counter["enginioChanged"], 0);
    }
    {
        EnginioClientConnectionSpy client;
        client.setBackendId(_backendId);
        client.setBackendSecret(_backendSecret);
        client.setServiceUrl(EnginioTests::TESTAPP_URL);

        EnginioModelConnectionSpy model;
        model.setEnginio(&client);
        QJsonObject query;
        query.insert("objectType", QString("objects.todos"));
        model.setQuery(query);

        for (int i = 0; i < 20; ++i) {
            model.setOperation(EnginioClient::ObjectOperation);
            model.setOperation(EnginioClient::ObjectAclOperation);
        }

        // The values here are not strict. Use qDebug() << model.counter; to see what
        // makes sense. Just to be sure 2097150 or 20 doesn't.
        QCOMPARE(model.counter["operationChanged"], 0);
        QCOMPARE(model.counter["queryChanged"], 0);
        QCOMPARE(model.counter["enginioChanged"], 0);
    }
}

struct StopDelayingFunctor
{
    EnginioReply *reply;
    StopDelayingFunctor(EnginioReply *r)
        : reply(r)
    {}
    void operator()()
    {
        reply->setDelayFinishedSignal(false);
    }
};

void tst_EnginioModel::deletionReordered()
{
    QJsonObject query = QJsonDocument::fromJson("{\"limit\":2}").object();
    QVERIFY(!query.isEmpty());
    EnginioModel model;
    model.disableNotifications();
    model.setQuery(query);
    model.setOperation(EnginioClient::UserOperation);

    EnginioClient client;
    QObject::connect(&client, SIGNAL(error(EnginioReply *)), this, SLOT(error(EnginioReply *)));
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);
    model.setEnginio(&client);

    QTRY_COMPARE(model.rowCount(), int(query["limit"].toDouble()));
    QVERIFY(model.rowCount() >= 2);

    EnginioReply *r2 = model.remove(model.rowCount() - 1);
    EnginioReply *r1 = model.remove(0);

    QVERIFY(!r1->isFinished());
    QVERIFY(!r2->isFinished());
    QVERIFY(!r1->isError());
    QVERIFY(!r2->isError());

    r2->setDelayFinishedSignal(true);
    StopDelayingFunctor activateR2(r2);
    QObject::connect(r1, &EnginioReply::finished, activateR2);

    int counter = 0;
    ReplyCounter replyCounter(&counter);
    QObject::connect(r1, &EnginioReply::finished, replyCounter);
    QObject::connect(r2, &EnginioReply::finished, replyCounter);

    QTRY_COMPARE(counter, 2);
}

void tst_EnginioModel::deleteTwiceTheSame()
{
    QJsonObject query = QJsonDocument::fromJson("{\"limit\":1}").object();
    QVERIFY(!query.isEmpty());
    EnginioModel model;
    model.disableNotifications();
    model.setQuery(query);
    model.setOperation(EnginioClient::UserOperation);

    EnginioClient client;
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);
    model.setEnginio(&client);

    QTRY_COMPARE(model.rowCount(), int(query["limit"].toDouble()));

    EnginioReply *r2 = model.remove(model.rowCount() - 1);
    EnginioReply *r1 = model.remove(model.rowCount() - 1);

    QVERIFY(!r1->isFinished());
    QVERIFY(!r2->isFinished());
    QVERIFY(!r1->isError());
    QVERIFY(!r2->isError());

    int counter = 0;
    ReplyCounter replyCounter(&counter);
    QObject::connect(r1, &EnginioReply::finished, replyCounter);
    QObject::connect(r2, &EnginioReply::finished, replyCounter);

    QTRY_COMPARE(counter, 2);

    // Sometimes server send us two positive message about deletion and
    // sometimes one positive and one 404.
    QVERIFY((r1->backendStatus() == 404 && !r2->isError())
            || (r2->backendStatus() == 404 && !r1->isError())
            || (!r1->isError() && !r2->isError()));
    // Check if the model is in sync with the backend, only one item should
    // be removed.
    QTRY_COMPARE(model.rowCount(), int(query["limit"].toDouble()) - 1);
}


void tst_EnginioModel::updateAndDeleteReordered()
{
    QJsonObject query = QJsonDocument::fromJson("{\"limit\":1}").object();
    QVERIFY(!query.isEmpty());
    EnginioModel model;
    model.disableNotifications();
    model.setQuery(query);
    model.setOperation(EnginioClient::UserOperation);

    EnginioClient client;
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);
    model.setEnginio(&client);

    QTRY_COMPARE(model.rowCount(), int(query["limit"].toDouble()));

    EnginioReply *r2 = model.setProperty(model.rowCount() - 1, "email", "email@email.com");
    EnginioReply *r1 = model.remove(model.rowCount() - 1);

    QVERIFY(!r1->isFinished());
    QVERIFY(!r2->isFinished());
    QVERIFY(!r1->isError());
    QVERIFY(!r2->isError());

    int counter = 0;
    ReplyCounter replyCounter(&counter);
    QObject::connect(r1, &EnginioReply::finished, replyCounter);
    QObject::connect(r2, &EnginioReply::finished, replyCounter);

    QTRY_COMPARE(counter, 2);

    // Sometimes server send us two positive message and
    // sometimes one positive and one 404.
    QVERIFY((r1->backendStatus() == 404 && !r2->isError())
            || (r2->backendStatus() == 404 && !r1->isError())
            || (!r1->isError() && !r2->isError()));
    // Check if the model is in sync with the backend, one item should
    // be removed.
    QTRY_COMPARE(model.rowCount(), int(query["limit"].toDouble()) - 1);
}

void tst_EnginioModel::updateReordered()
{
    QJsonObject query = QJsonDocument::fromJson("{\"limit\":1}").object();
    QVERIFY(!query.isEmpty());
    EnginioModel model;
    model.disableNotifications();
    model.setQuery(query);
    model.setOperation(EnginioClient::UserOperation);

    EnginioClient client;
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);
    model.setEnginio(&client);

    QTRY_COMPARE(model.rowCount(), int(query["limit"].toDouble()));

    int counter = 0;

    EnginioReply *r2 = model.setProperty(0, "email", "email2@email.com");
    QVERIFY(!r2->isError());
    r2->setDelayFinishedSignal(true);

    ReplyCounter replyCounter(&counter);
    QObject::connect(r2, &EnginioReply::finished, replyCounter);

    QTRY_VERIFY(!r2->data().isEmpty()); // at this point r2 is done but finished signal is not emited
    QTRY_COMPARE(counter, 0);

    EnginioReply *r1 = model.setProperty(0, "email", "email1@email.com");
    QVERIFY(!r1->isError());

    QObject::connect(r1, &EnginioReply::finished, replyCounter);
    StopDelayingFunctor activateR2(r2);
    QObject::connect(r1, &EnginioReply::finished, activateR2);

    QTRY_COMPARE(counter, 2);

    QDateTime r1UpdatedAt = QDateTime::fromString(r1->data()["updatedAt"].toString(), Qt::ISODate);
    QDateTime r2UpdatedAt = QDateTime::fromString(r2->data()["updatedAt"].toString(), Qt::ISODate);

    QVERIFY(r2UpdatedAt < r1UpdatedAt);
    QCOMPARE(model.data(model.index(0)).value<QJsonValue>().toObject(), r1->data());
}

void tst_EnginioModel::append()
{
    QString propertyName = "title";
    QString objectType = "objects." + EnginioTests::CUSTOM_OBJECT1;
    QJsonObject query;
    query.insert("objectType", objectType); // should be an empty set

    EnginioClient client;
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);

    EnginioModel model;
    model.disableNotifications();
    model.setQuery(query);

    QObject::connect(&client, SIGNAL(error(EnginioReply *)), this, SLOT(error(EnginioReply *)));

    {   // init the model
        QSignalSpy spy(&model, SIGNAL(modelReset()));
        model.setEnginio(&client);

        QTRY_VERIFY(spy.count() > 0);
    }
    {
        // add two items to an empy model
        QCOMPARE(model.rowCount(), 0);
        QJsonObject o1, o2;
        o1.insert(propertyName, QString::fromLatin1("o1"));
        o1.insert("objectType", objectType);
        o2.insert(propertyName, QString::fromLatin1("o2"));
        o2.insert("objectType", objectType);

        EnginioReply *r1 = model.append(o1);
        EnginioReply *r2 = model.append(o2);
        QVERIFY(r1);
        QVERIFY(r2);

        QCOMPARE(model.rowCount(), 2);

        // check data content
        QCOMPARE(model.data(model.index(0)).value<QJsonValue>().toObject(), o1);
        QCOMPARE(model.data(model.index(1)).value<QJsonValue>().toObject(), o2);

        // check synced flag, the data is not synced yet
        QCOMPARE(model.data(model.index(0), EnginioModel::SyncedRole).value<bool>(), false);
        QCOMPARE(model.data(model.index(1), EnginioModel::SyncedRole).value<bool>(), false);

        // check synced flag, the data should be in sync at some point
        QTRY_COMPARE(model.data(model.index(0), EnginioModel::SyncedRole).value<bool>(), true);
        QTRY_COMPARE(model.data(model.index(1), EnginioModel::SyncedRole).value<bool>(), true);
    }
    {
        // add a new item and remove earlier the first item
        QVERIFY(model.rowCount() > 0);
        QJsonObject o3;
        o3.insert(propertyName, QString::fromLatin1("o3"));
        o3.insert("objectType", objectType);

        // check if everything is in sync
        for (int i = 0; i < model.rowCount(); ++i)
            QCOMPARE(model.data(model.index(i), EnginioModel::SyncedRole).value<bool>(), true);

        const int initialRowCount = model.rowCount();
        // the real test
        EnginioReply *r3 = model.append(o3);
        QVERIFY(r3);
        QVERIFY(!r3->isFinished());
        r3->setDelayFinishedSignal(true);
        QCOMPARE(model.data(model.index(initialRowCount), EnginioModel::SyncedRole).value<bool>(), false);

        EnginioReply *r4 = model.remove(0);

        QCOMPARE(model.data(model.index(0), EnginioModel::SyncedRole).value<bool>(), false);
        QCOMPARE(model.data(model.index(initialRowCount), EnginioModel::SyncedRole).value<bool>(), false);

        int counter = 0;
        ReplyCounter replyCounter(&counter);
        QObject::connect(r3, &EnginioReply::finished, replyCounter);
        QObject::connect(r4, &EnginioReply::finished, replyCounter);

        QTRY_COMPARE(counter, 1);
        QVERIFY(r4->isFinished());
        // at this point the first value was deleted but append is still not confirmed
        QCOMPARE(r3->delayFinishedSignal(), true);
        QCOMPARE(model.rowCount(), initialRowCount); // one added and one removed

        for (int i = 0; i < model.rowCount() - 1; ++i) {
            QCOMPARE(model.data(model.index(i), EnginioModel::SyncedRole).value<bool>(), true);
        }
        {
            QModelIndex idx = model.index(initialRowCount - 1);
            QCOMPARE(model.data(idx, EnginioModel::SyncedRole).value<bool>(), false);
            QCOMPARE(model.data(idx).value<QJsonValue>().toObject(), o3);
        }

        r3->setDelayFinishedSignal(false);
        QVERIFY(!client.finishDelayedReplies());
        QTRY_COMPARE(counter, 2);
        // everything should be done
        QCOMPARE(model.rowCount(), initialRowCount);
        QVERIFY(r4->isFinished());
        QVERIFY(r3->isFinished());

        // check if everything is in sync
        for (int i = 0; i < model.rowCount(); ++i)
            QCOMPARE(model.data(model.index(i), EnginioModel::SyncedRole).value<bool>(), true);

        QModelIndex idx = model.index(initialRowCount - 1);
        QCOMPARE(model.data(idx).value<QJsonValue>().toObject()[propertyName], o3[propertyName]);
    }
}

template<class T>
void tst_EnginioModel::externallyRemovedImpl()
{
    T operation;
    // Remove an item from model which was removed earlier from server
    QString propertyName = operation.propertyName();
    QString objectType = "objects." + EnginioTests::CUSTOM_OBJECT1;
    QJsonObject query;
    query.insert("objectType", objectType);
    query.insert("limit", 1);

    EnginioClient client;
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);

    {
        QJsonObject o;
        o.insert(propertyName, QString::fromLatin1("IWillBeRemoved"));
        o.insert("objectType", objectType);
        EnginioReply *r = client.create(o);
        QTRY_VERIFY(r->isFinished());
        QVERIFY(!r->isError());
    }

    EnginioModel model;
    model.disableNotifications();
    model.setQuery(query);

    {   // init the model
        QSignalSpy spy(&model, SIGNAL(modelReset()));
        model.setEnginio(&client);

        QTRY_VERIFY(spy.count() > 0);
        QVERIFY(model.rowCount());
    }
    QModelIndex i = model.index(0);
    QString id = model.data(i, EnginioModel::IdRole).value<QJsonValue>().toString();
    QVERIFY(!id.isEmpty());

    QJsonObject o;
    o.insert("id", id);
    o.insert("objectType", objectType);
    EnginioReply *r1 = client.remove(o);
    QTRY_VERIFY(r1->isFinished());

    // the value was removed on the server side,
    QCOMPARE(model.data(i, EnginioModel::IdRole).value<QJsonValue>().toString(), id);
    // but is still in the model cache.

    EnginioReply *r2 = operation(model, 0);

    QTRY_VERIFY(r2->isFinished());
    QVERIFY(r2->isError());
    QCOMPARE(r2->backendStatus(), 404); // abviously item was not found on the server side

    // Let's check if the model was updated
    i = model.index(0);
    QCOMPARE(model.rowCount(), 0);
}

struct ExternallyRemovedSetProperty
{
    EnginioReply *operator()(EnginioModel &model, int row) const
    {
        return model.setProperty(row, propertyName(), "areYouDeleted?");
    }
    QString propertyName() const
    {
        return "title";
    }
};

void tst_EnginioModel::setPropertyOnExternallyRemovedObject()
{
    externallyRemovedImpl<ExternallyRemovedSetProperty>();
}

struct ExternallyRemovedRemove
{
    EnginioReply *operator()(EnginioModel &model, int row) const
    {
        return model.remove(row);
    }
    QString propertyName() const
    {
        return "title";
    }
};

void tst_EnginioModel::removeExternallyRemovedObject()
{
    externallyRemovedImpl<ExternallyRemovedRemove>();
}

void tst_EnginioModel::createAndModify()
{
    EnginioClient client;
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);;

    QString propertyName = "title";
    QString objectType = "objects." + EnginioTests::CUSTOM_OBJECT1;
    QJsonObject query;
    query.insert("objectType", objectType);
    query.insert("limit", 1);

    EnginioModel model;
    model.disableNotifications();
    model.setQuery(query);
    {   // init the model
        QSignalSpy spy(&model, SIGNAL(modelReset()));
        model.setEnginio(&client);
        QTRY_VERIFY(spy.count() > 0);
    }

    QJsonObject o;
    o.insert(propertyName, QString::fromLatin1("o"));
    o.insert("objectType", objectType);

    {
        // create and immediatelly remove
        const int initialRowCount = model.rowCount();
        EnginioReply *r1 = model.append(o);
        QVERIFY(!r1->isFinished());
        QVERIFY(!r1->isError());

        EnginioReply *r2 = model.remove(model.rowCount() - 1);
        QVERIFY(!r2->isFinished());
        QVERIFY(!r2->isError());
        r2->setDelayFinishedSignal(true);

        QTRY_VERIFY(r1->isFinished());
        QModelIndex i = model.index(model.rowCount() - 1);
        QCOMPARE(model.data(i, EnginioModel::SyncedRole).value<bool>(), false);
        r2->setDelayFinishedSignal(false);

        QTRY_VERIFY(r2->isFinished());
        QVERIFY(!r2->isError());
        QTRY_COMPARE(model.rowCount(), initialRowCount);
    }
    {
        // create and immediatelly update
        const int initialRowCount = model.rowCount();
        EnginioReply *r1 = model.append(o);
        QVERIFY(!r1->isFinished());
        QVERIFY(!r1->isError());

        EnginioReply *r2 = model.setProperty(model.rowCount() - 1, propertyName, QString::fromLatin1("newO"));
        QVERIFY(!r2->isFinished());
        QVERIFY(!r2->isError());
        r2->setDelayFinishedSignal(true);

        QTRY_VERIFY(r1->isFinished());
        QModelIndex i = model.index(model.rowCount() - 1);
        QCOMPARE(model.data(i, EnginioModel::SyncedRole).value<bool>(), false);
        r2->setDelayFinishedSignal(false);

        QTRY_VERIFY(r2->isFinished());
        QCOMPARE(model.rowCount(), initialRowCount + 1);
        QVERIFY(!r2->isError());
        i = model.index(model.rowCount() - 1);
        QCOMPARE(model.data(i).value<QJsonValue>().toObject()["title"].toString(), QString::fromLatin1("newO"));
        QCOMPARE(model.data(i, EnginioModel::SyncedRole).value<bool>(), true);
    }
}

int externalNotificationFindHelper(EnginioModel &model, const QString propertyName, const QJsonObject &o)
{
    for (int idx = 0; idx < model.rowCount(); ++idx) {
        QModelIndex i = model.index(idx);
        if (model.data(i).toJsonValue().toObject()[propertyName].toString()
                == o[propertyName].toString()) {
            return idx;
        }
    }
    return -1;
}

void tst_EnginioModel::externalNotification()
{
    if (EnginioTests::TESTAPP_URL != "https://staging.engin.io")
        QSKIP("The test depands on notifications, which are enabled only in staging environment");

    EnginioClient client;
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);

    QString propertyName = "title";
    QString objectType = "objects." + EnginioTests::CUSTOM_OBJECT1;
    QJsonObject query;
    query.insert("objectType", objectType);

    EnginioModel model;
    model.setQuery(query);
    {   // init the model
        QSignalSpy spy(&model, SIGNAL(modelReset()));
        model.setEnginio(&client);
        QTRY_VERIFY(spy.count() > 0);
    }

    QJsonObject o;
    o.insert(propertyName, QString::fromLatin1("externalNotification"));
    o.insert("objectType", objectType);
    {
        // insert a new object
        //TODO should we wait for the websocket?
        const int initialRowCount = model.rowCount();

        EnginioReply *r = client.create(o);
        QTRY_VERIFY(r->isFinished());
        QVERIFY(!r->isError());
        o = r->data();
        QTRY_COMPARE(model.rowCount(), initialRowCount + 1);
        QVERIFY(externalNotificationFindHelper(model, propertyName, o) != -1);
    }
    {
        // modify an object
        o.insert(propertyName, QString::fromLatin1("externalNotification_modified"));
        EnginioReply *r = client.update(o);
        QTRY_VERIFY(r->isFinished());

        QVERIFY(!r->isError());

        int idx;
        for (idx = 0; idx < model.rowCount(); ++idx) {
            QModelIndex i = model.index(idx);
            if (model.data(i).toJsonValue().toObject()[propertyName].toString()
                    == o[propertyName].toString()) {
                break;
            }
        }
        QTRY_VERIFY(externalNotificationFindHelper(model, propertyName, o) != -1);
    }
    {
        // remove an object
        const int initialRowCount = model.rowCount();

        EnginioReply *r = client.remove(o);
        QTRY_VERIFY(r->isFinished());
        QTRY_COMPARE(model.rowCount(), initialRowCount - 1);

        int idx;
        for (idx = 0; idx < model.rowCount(); ++idx) {
            QModelIndex i = model.index(idx);
            if (model.data(i).toJsonValue().toObject()[propertyName].toString()
                    == o[propertyName].toString()) {
                break;
            }
        }
        QTRY_VERIFY(externalNotificationFindHelper(model, propertyName, o) == -1);
    }
}

void tst_EnginioModel::createUpdateRemoveWithNotification()
{
    EnginioClient client;
    client.setBackendId(_backendId);
    client.setBackendSecret(_backendSecret);
    client.setServiceUrl(EnginioTests::TESTAPP_URL);

    QString propertyName = "title";
    QString objectType = "objects." + EnginioTests::CUSTOM_OBJECT1;
    QJsonObject query;
    query.insert("objectType", objectType);

    EnginioModel model;
    model.setQuery(query);
    {   // init the model
        QSignalSpy spy(&model, SIGNAL(modelReset()));
        model.setEnginio(&client);
        QTRY_VERIFY(spy.count() > 0);
    }

    const int repliesCount = 12;
    const int initialCount = model.rowCount();
    QJsonObject o;
    o.insert("objectType", objectType);

    QVector<EnginioReply *> replies;
    replies.reserve(repliesCount);
    for (int i = 0; i < replies.capacity(); ++i) {
        o.insert(propertyName, QString::fromLatin1("withNotification") + QString::number(i));
        replies << model.append(o);
    }

    // wait for responses first, then for rowCount
    // so if the test is broken rowCount would be bigger then replies.count()
    foreach (EnginioReply *reply, replies) {
        QTRY_VERIFY_WITH_TIMEOUT(reply->isFinished(), 10000);
        QVERIFY(!reply->isError());
    }
    QTRY_COMPARE(model.rowCount(), initialCount + repliesCount);


    // lets try to update our objects
    replies.resize(0);
    for (int i = 0; i < model.rowCount(); ++i) {
        QModelIndex idx = model.index(i);
        QJsonObject o = model.data(idx).toJsonValue().toObject();
        if (o[propertyName].toString().startsWith("withNotification")) {
            replies << model.setProperty(i, propertyName, QString::fromLatin1("withNotification_mod"));
        }
    }
    QVERIFY(replies.count() == repliesCount);
    foreach (EnginioReply *reply, replies) {
        QTRY_VERIFY_WITH_TIMEOUT(reply->isFinished(), 10000);
        QVERIFY(!reply->isError());
    }
    QTRY_COMPARE(model.rowCount(), initialCount + repliesCount);
    int counter = 0;
    for (int i = 0; i < model.rowCount(); ++i) {
        QModelIndex idx = model.index(i);
        QJsonObject o = model.data(idx).toJsonValue().toObject();
        if (o[propertyName].toString().startsWith("withNotification_mod")) {
            counter++;
        }
    }
    QCOMPARE(counter, repliesCount);

    // lets remove our objects
    replies.resize(0);
    for (int i = 0; i < model.rowCount(); ++i) {
        QModelIndex idx = model.index(i);
        QJsonObject o = model.data(idx).toJsonValue().toObject();
        if (o[propertyName].toString().startsWith("withNotification")) {
            replies << model.remove(i);
        }
    }
    QCOMPARE(replies.count(), repliesCount);
    foreach (EnginioReply *reply, replies) {
        QTRY_VERIFY_WITH_TIMEOUT(reply->isFinished(), 10000);
        QVERIFY(!reply->isError());
    }
    QTRY_COMPARE(model.rowCount(), initialCount);
}

QTEST_MAIN(tst_EnginioModel)
#include "tst_enginiomodel.moc"
