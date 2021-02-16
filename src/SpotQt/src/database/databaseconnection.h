#pragma once

#include <QString>
#include <QtSql/QSqlDatabase>

class DataBaseConnection
{
    explicit DataBaseConnection() = default;
    ~DataBaseConnection() = default;

    static bool open(const QString &connectionName);

    static bool opened(const QString &connectionName);

    static void close(const QString &connectionName);

    static QSqlDatabase create(const QString &connectionName);

    static void destroy(const QString &connectionName);

    friend class AbstractDao;
};

