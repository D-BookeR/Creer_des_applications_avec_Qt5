#include "sqlext.h"

SQLExtDatabase::SQLExtDatabase(const QString &hostname, const QString &database,
    const QString &user, const QString &password)
    : QObject(), m_connectionName(hostname + ":" + database)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", m_connectionName);
    db.setHostName(hostname);
    db.setDatabaseName(database);
    db.setUserName(user);
    db.setPassword(password);
    db.open();
}

SQLExtDatabase::~SQLExtDatabase()
{
    QSqlDatabase::removeDatabase(m_connectionName);
}

bool SQLExtDatabase::isOpen() const
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    return db.isValid() && db.isOpen();
}

QVariant SQLExtDatabase::executeSql(const QString &q) const
{
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query = db.exec(q);
    bool error = query.lastError().type() != QSqlError::NoError;
    QJsonObject res;

    res.insert("error", error);

    if (error)
    {
        res.insert("errorStr", query.lastError().text());
        return res;
    }

    if (query.isSelect())
    {
        QJsonArray rows;
        int size = 0;
        int fields = query.record().count();
        while (query.next())
        {
            QJsonObject value;
            for (int i = 0; i < fields; ++i)
                value.insert(query.record().fieldName(i), query.value(i).toString());
            rows.append(value);
            ++size;
        }
        res.insert("length", size);
        res.insert("items", rows);
        return res;
    }

    res.insert("rowsAffected", query.numRowsAffected());
    res.insert("insertId", query.lastInsertId().toString());
    return res;
}

SQLExt::SQLExt(QObject *parent)
    : QObject(parent)
{
}

SQLExt::~SQLExt()
{
    foreach (SQLExtDatabase *db, m_dbs)
        delete db;
}

void SQLExt::freeDatabaseSync(const QVariant &db)
{
    if (db.canConvert<SQLExtDatabase *>())
    {
        SQLExtDatabase *database = db.value<SQLExtDatabase *>();
        m_dbs.removeOne(database);
        delete database;
    }
}

SQLExtDatabase *SQLExt::openDatabaseSync(const QString &hostname, const QString &database,
    const QString &user, const QString &password)
{
    SQLExtDatabase *obj = new SQLExtDatabase(hostname, database, user, password);
    m_dbs.append(obj);
    return obj;
}
