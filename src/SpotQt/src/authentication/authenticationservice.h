#pragma once

#include <QObject>
#include <QThread>
#include <QNetworkAccessManager>
#include <QTcpServer>

#include <memory>

#include "authenticationgui.h"

class AuthenticationService : public QObject
{
    Q_OBJECT
public:
    explicit AuthenticationService(QObject *parent = nullptr);
    ~AuthenticationService() override;

    bool needToAuthenticate() const;

    void startAuthenticationService();

    void endAuthenticationService();

    QString getClientId() const;
    void setClientId(const QString &clientId);

    QString getClientSecret() const;
    void setClientSecret(const QString &clientSecret);

signals:
    void authenticated();
    void authenticationFailed();

private slots:
    void parseHttpRequest();

    QString getSpotifyAuthUrl();

private:
    bool m_authenticated;
    QString m_clientId;
    QString m_clientSecret;

    QThread m_threadAuthBrowser;
    std::unique_ptr<AuthenticationGui> m_authBrowser;
    std::unique_ptr<QNetworkAccessManager> m_networkAccessManager;
    std::unique_ptr<QTcpServer> m_tcpServer;
};

