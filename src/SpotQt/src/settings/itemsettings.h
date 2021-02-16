#pragma once

#include <QObject>
#include <QString>
#include <QVariant>

class ItemSettings : public QObject
{
    Q_OBJECT
public:
    explicit ItemSettings(QObject *parent = nullptr);

    unsigned int id() const;
    void setId(unsigned int id);

    QString field() const;
    void setField(const QString &field);

    QVariant value() const;
    void setValue(const QVariant &value);

    QVariant extra() const;
    void setExtra(const QVariant &extra);

signals:
    void idChanged();
    void fieldChanged();
    void valueChanged();
    void extraChanged();

private:
    unsigned int m_id;
    QString m_field;
    QVariant m_value;
    QVariant m_extra;
};

