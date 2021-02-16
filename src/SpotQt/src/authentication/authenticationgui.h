#pragma once

#include <QObject>
#include <memory>

#include <QQmlApplicationEngine>

class AuthenticationGui : public QObject
{
    Q_OBJECT
public:
    explicit AuthenticationGui(QObject *parent = nullptr);

    void openBrowser(const QString &url);

private:
    std::unique_ptr<QQmlApplicationEngine> engine;
};

