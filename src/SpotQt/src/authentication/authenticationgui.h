#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

class AuthenticationGui : public QObject
{
    Q_OBJECT
public:
    explicit AuthenticationGui(QObject *parent = nullptr);

    void openBrowser(const QString &url);

signals:

private:
    QQmlApplicationEngine engine;
};

