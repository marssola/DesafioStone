#include "itemsettings.h"

ItemSettings::ItemSettings(QObject *parent) :
    QObject(parent),
    m_id(0),
    m_field(QStringLiteral(""))
{}

unsigned int ItemSettings::id() const
{
    return m_id;
}

void ItemSettings::setId(unsigned int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged();
}

QString ItemSettings::field() const
{
    return m_field;
}

void ItemSettings::setField(const QString &field)
{
    if (m_field == field)
        return;

    m_field = field;
    emit fieldChanged();
}

QVariant ItemSettings::value() const
{
    return m_value;
}

void ItemSettings::setValue(const QVariant &value)
{
    if (m_value == value)
        return;

    m_value = value;
    emit valueChanged();
}

QVariant ItemSettings::extra() const
{
    return m_extra;
}

void ItemSettings::setExtra(const QVariant &extra)
{
    if (m_extra == extra)
        return;

    m_extra = extra;
    emit extraChanged();
}
