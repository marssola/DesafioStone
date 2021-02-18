#pragma once

#include "databaseconnection.h"

class AbstractDao : public DataBaseConnection
{
public:
    explicit AbstractDao();
    ~AbstractDao();

    enum class TypeQuery
    {
        All = 0x1
    };

    bool openConnection();
    bool isOpen();
    void closeConnection();

    QSqlDatabase &getConnection();

    virtual void createTable() = 0;

private:
    const QString m_connectionName;
    QSqlDatabase m_connection;
};

