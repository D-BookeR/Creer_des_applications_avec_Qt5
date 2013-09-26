#ifndef SQLEXT_H
#define SQLEXT_H

#include <QtQuick>
#include <QtCore>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlResult>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

class SQLExtDatabase : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SQLExtDatabase)

public:
    SQLExtDatabase(const QString &hostname, const QString &database,
        const QString &user, const QString &password);
    virtual ~SQLExtDatabase();

    Q_INVOKABLE bool isOpen() const;
    Q_INVOKABLE QVariant executeSql(const QString &q) const;

private:
    QString m_connectionName;
};

class SQLExt : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SQLExt)

public:
    SQLExt(QObject *parent = NULL);
    virtual ~SQLExt();

    Q_INVOKABLE void freeDatabaseSync(const QVariant &db);
    Q_INVOKABLE SQLExtDatabase *openDatabaseSync(const QString &hostname, const QString &database,
        const QString &user, const QString &password);

private:
    QList<SQLExtDatabase *> m_dbs;
};

QML_DECLARE_TYPE(SQLExt)
QML_DECLARE_TYPE(SQLExtDatabase)

#endif // SQLEXT_H
