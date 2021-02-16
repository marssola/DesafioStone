#pragma once

#include "databaseconnection.h"

class AbstractDao : public DataBaseConnection
{
public:
    explicit AbstractDao();
    ~AbstractDao();

    bool openConnection();
    bool isOpen();
    void closeConnection();

    QSqlDatabase &getConnection();

    virtual void createTable() = 0;

private:
    const QString m_connectionName;
    QSqlDatabase m_connection;
};

