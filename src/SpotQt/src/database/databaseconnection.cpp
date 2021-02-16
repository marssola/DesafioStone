#include "databaseconnection.h"
#include <QtSql/QSqlError>
#include <QDebug>

#include <QFileInfo>
#include <QDir>

bool DataBaseConnection::open(const QString &connectionName)
{
    if (opened(connectionName))
        return true;

    QSqlDatabase db = QSqlDatabase::database(connectionName);
    if (db.open())
        return true;

    qCritical() << "Error trying to connect database" << connectionName;
    qCritical() << db.lastError();
    return false;
}

bool DataBaseConnection::opened(const QString &connectionName)
{
    return QSqlDatabase::database(connectionName).isOpen();
}

void DataBaseConnection::close(const QString &connectionName)
{
    if (opened(connectionName))
        QSqlDatabase::database(connectionName).close();
}

QSqlDatabase DataBaseConnection::create(const QString &connectionName)
{
    QDir dir;
    if (!dir.exists(ROOT_PATH))
        dir.mkpath(ROOT_PATH);
    const QString &databaseName(QStringLiteral("%1/db/%2SpotQt.db").arg(ROOT_PATH, TEST));

    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), connectionName);
    db.setDatabaseName(databaseName);
    return db;
}

void DataBaseConnection::destroy(const QString &connectionName)
{
    if (QSqlDatabase::contains(connectionName))
        QSqlDatabase::removeDatabase(connectionName);
}
