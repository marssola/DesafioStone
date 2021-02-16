#include "settings.h"
#include <algorithm>

Settings::Settings(QObject *parent) :
    QObject(parent)
{}

Settings::~Settings()
{
    std::remove_if(std::begin(m_settings), std::end(m_settings), [](ItemSettings *item) { delete item; return true; });
    m_settings.clear();
}

int Settings::size() const
{
    return m_settings.size();
}

bool Settings::loadAll(Settings &settings)
{
    return settingsDao.loadAll(&settings);
}

bool Settings::updateItems()
{
    return settingsDao.update(m_settings);
}

QMap<int, ItemSettings *> Settings::getSettings()
{
    return m_settings;
}

ItemSettings *Settings::getItemSettings(Settings::Type type)
{
    return m_settings[static_cast<int>(type)];
}

void Settings::setItemSettings(ItemSettings *item, bool notifyChanged)
{
    if (m_settings.contains(item->id()))
        delete m_settings[item->id()];

    m_settings[item->id()] = item;
    if (notifyChanged)
        emit settingsChanged();
}
