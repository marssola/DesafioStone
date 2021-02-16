#include "settingsdao.h"
#include "itemsettings.h"
#include "settings.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

SettingsDao::SettingsDao():
    m_table(QStringLiteral("settings"))
{
    createTable();
}

bool SettingsDao::loadAll(Settings *settings)
{
    if (!openConnection()) {
        qCritical() << "Error trying open connection database" << getConnection().lastError().text();
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(getQueryStr(TypeQuery::All));
    return readData(query, settings);
}

bool SettingsDao::update(QMap<int, ItemSettings *> &settings)
{
    if (!openConnection()) {
        qCritical() << "Error trying open connection database" << getConnection().lastError().text();
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("INSERT OR REPLACE INTO %1 (id, field, value, extra) VALUES(:id, :field, :value, :extra)").arg(m_table));

    QVariantList ids{};
    QVariantList fields{};
    QVariantList values{};
    QVariantList extras{};

    for (auto &item : settings) {
        ids << item->id();
        fields << item->field();
        values << item->value();
        extras << item->extra();
    }

    query.bindValue(QStringLiteral(":id"), ids);
    query.bindValue(QStringLiteral(":field"), fields);
    query.bindValue(QStringLiteral(":value"), values);
    query.bindValue(QStringLiteral(":extra"), extras);

    const bool exec = query.execBatch();
    if (!exec)
        qCritical() << "Error trying INSERT or REPLACE" << query.lastError().text();
    closeConnection();
    return exec;
}

void SettingsDao::createTable()
{
    if (!openConnection()) {
        qCritical() << "Error trying open database" << getConnection().lastError().text();
        return;
    }

    const QString createTableStr(QStringLiteral("CREATE TABLE IF NOT EXISTS %1 ("
            "id INTEGER UNIQUE,"
            "field TEXT UNIQUE,"
            "value TEXT,"
            "extra TEXT,"
            "PRIMARY KEY(id)"
        ");").arg(m_table));

    QSqlQuery query(getConnection());
    query.prepare(createTableStr);

    if (!query.exec())
        qCritical() << "Error trying create database" << query.lastError().text();

    const QString insertStr(QStringLiteral("INSERT OR IGNORE INTO %1 (id, field, value) VALUES(:id, :field, :value)").arg(m_table));
    query.prepare(insertStr);

    QVariantList ids {
        static_cast<int>(Settings::Type::ClientID),
        static_cast<int>(Settings::Type::ClientSecret),
        static_cast<int>(Settings::Type::UserToken),
        static_cast<int>(Settings::Type::TokenExpires)
    };
    QVariantList fields {
        QStringLiteral("ClientID"),
        QStringLiteral("ClientSecret"),
        QStringLiteral("UserToken"),
        QStringLiteral("TokenExpires")
    };
    QVariantList values {
        QStringLiteral("f8023ea988e548df83fb42b5ce1e1a20"),
        QStringLiteral("5cf01313067d4391a9a8643add01307a"),
        QStringLiteral(""),
        QStringLiteral("")
    };

    query.bindValue(QStringLiteral(":id"), ids);
    query.bindValue(QStringLiteral(":field"), fields);
    query.bindValue(QStringLiteral(":value"), values);

    if (!query.execBatch())
        qCritical() << "Error trying INSERT registers" << query.lastError().text();

    closeConnection();
}

bool SettingsDao::readData(QSqlQuery &query, Settings *settings)
{
    const bool exec = query.exec();
    if (!exec) {
        qCritical() << "Error trying read data" << query.lastError().text();
    } else {
        constexpr auto fieldId = 0;
        constexpr auto fieldField = 1;
        constexpr auto fieldValue = 2;
        constexpr auto fieldExtra = 3;

        while (query.next()) {
            ItemSettings *item = new ItemSettings;
            item->setId(query.value(fieldId).toInt());
            item->setField(query.value(fieldField).toString());
            item->setValue(query.value(fieldValue));
            item->setExtra(query.value(fieldExtra));

            settings->setItemSettings(item, false);
        }

        emit settings->settingsChanged();
    }

    closeConnection();
    return exec;
}

QString SettingsDao::getQueryStr(SettingsDao::TypeQuery type)
{
    QString queryStr(QStringLiteral("SELECT"));
    switch (type) {
    case TypeQuery::All:
        queryStr += QStringLiteral(" id, field, value, extra");
        break;
    }
    queryStr += QStringLiteral(" FROM %1").arg(m_table);

    return queryStr;
}
