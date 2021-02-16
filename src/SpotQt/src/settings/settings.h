#pragma once

#include <QObject>
#include <QMap>

#include "itemsettings.h"
#include "settingsdao.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    ~Settings() override;

    enum class Type
    {
        ClientID = 0x1,
        ClientSecret,
        AuthorizationCode,
        UserToken
    };

    int size() const;

    bool loadAll(Settings &settings);

    bool updateItems();

    QMap<int, ItemSettings *> getSettings();

    ItemSettings *getItemSettings(Type type);

    void setItemSettings(ItemSettings *item, bool notifyChanged = true);

signals:
    void settingsChanged();

private:
    QMap<int, ItemSettings *> m_settings;
    SettingsDao settingsDao;
};

