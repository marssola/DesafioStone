#include "abstractdao.h"
#include "QUuid"

AbstractDao::AbstractDao():
    m_connectionName(QUuid::createUuid().toString()),
    m_connection(create(m_connectionName))
{}

AbstractDao::~AbstractDao()
{
    m_connection = QSqlDatabase();
    destroy(m_connectionName);
}

bool AbstractDao::openConnection()
{
    return open(m_connectionName);
}

bool AbstractDao::isOpen()
{
    return opened(m_connectionName);
}

void AbstractDao::closeConnection()
{
    close(m_connectionName);
}

QSqlDatabase &AbstractDao::getConnection()
{
    return m_connection;
}
