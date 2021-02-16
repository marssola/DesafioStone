#pragma once

#include "../database/abstractdao.h"
#include <QString>

class Settings;
class ItemSettings;

class SettingsDao : public AbstractDao
{
    const QString m_table;

public:
    SettingsDao();

    enum class TypeQuery
    {
        All = 0x1
    };

    bool loadAll(Settings *settings);

    bool update(QMap<int, ItemSettings *> &settings);

private:
    void createTable() override;

    bool readData(QSqlQuery &query, Settings *settings);

    QString getQueryStr(TypeQuery type);
};

