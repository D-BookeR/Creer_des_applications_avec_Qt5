#ifndef ENGINIOTESTSCOMMON_H
#define ENGINIOTESTSCOMMON_H

#include <Enginio/enginioclient.h>
#include <QtCore/qmap.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qurl.h>

#if !defined(QTRY_VERIFY)
#error QtTest library has to be included before common.h
#endif

#undef QTRY_VERIFY
#undef QTRY_COMPARE

#define QTRY_VERIFY(Test) QTRY_VERIFY_WITH_TIMEOUT(Test, 15000)
#define QTRY_COMPARE(Test1, Test2) QTRY_COMPARE_WITH_TIMEOUT(Test1, Test2, 15000)

#define CHECK_NO_ERROR(response) \
    QVERIFY(response->isFinished()); \
    QVERIFY(!response->isError()); \
    QCOMPARE(response->errorType(), EnginioReply::NoError);\
    QCOMPARE(response->networkError(), QNetworkReply::NoError);\
    QVERIFY(response->backendStatus() >= 200 && response->backendStatus() < 300);


class EnginioReply;

namespace EnginioTests
{

const QString TESTAPP_URL(qgetenv("ENGINIO_API_URL"));
const QString TESTAPP_ENV = QStringLiteral("development");
const QString CUSTOM_OBJECT1(QStringLiteral("CustomObject1"));
const QString CUSTOM_OBJECT2(QStringLiteral("CustomObject2"));

class EnginioBackendManager: public QObject
{
    Q_OBJECT

    EnginioClient _client;
    QJsonObject _headers;
    QJsonObject _responseData;
    QMap<QString, QJsonArray> _backendEnvironments;
    QString _email;
    QString _password;
    QUrl _url;

    bool synchronousRequest(const QByteArray &httpOperation, const QJsonObject &data = QJsonObject());
    bool removeAppWithId(const QString &appId);
    bool authenticate();
    QString getAppId(const QString &backendName) Q_REQUIRED_RESULT;
    QJsonArray getAllBackends() Q_REQUIRED_RESULT;
    QJsonArray getEnvironments(const QString &backendName);

public slots:
    void error(EnginioReply *reply);
    void finished(EnginioReply* reply);

public:
    explicit EnginioBackendManager(QObject *parent = 0);
    virtual ~EnginioBackendManager();
    void setServiceUrl(const QUrl &serviceUrl);
    bool createBackend(const QString &backendName);
    bool removeBackend(const QString &backendName);
    bool createObjectType(const QString &backendName, const QString &environment, const QJsonObject &schema);
    QJsonObject backendApiKeys(const QString &backendName, const QString &environment);
};

void prepareTestUsersAndUserGroups(const QByteArray &backendId, const QByteArray &backendSecret);
bool prepareTestObjectType(const QString &backendName);

}

#endif // ENGINIOTESTSCOMMON_H
