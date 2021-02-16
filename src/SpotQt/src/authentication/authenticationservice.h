#pragma once

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QDateTime>

#include <memory>

#include "authenticationgui.h"

class AuthenticationService : public QObject
{
    Q_OBJECT
public:
    explicit AuthenticationService(QObject *parent = nullptr);
    ~AuthenticationService() override;

    bool needAuthentication();

    void startAuthenticationService();
    void endAuthenticationService();

    void getSpotifyToken();

    QString getClientId() const;
    void setClientId(const QString &clientId);

    QString getClientSecret() const;
    void setClientSecret(const QString &clientSecret);

    QString getAuthorizationCode() const;
    void setAuthorizationCode(const QString &authorizationCode);

    QString getUserToken() const;
    void setUserToken(const QString &userToken);

    QDateTime getTokenExpires() const;
    void setTokenExpires(const QDateTime &tokenExpires);

signals:
    void authenticated();
    void authenticationFailed();
    void authenticationChanged();
    void newConnection();
    void httpParsed();

    void clientIdChanged();
    void clientSecretChanged();
    void authorizationCodeChanged();
    void userTokenChanged();
    void tokenExpiresChanged();

private slots:
    void parseHttpRequest();

    QString getSpotifyAuthUrl();    

private:
    bool m_authenticated;
    QString m_clientId;
    QString m_clientSecret;
    QString m_authorizationCode;
    QString m_userToken;
    QDateTime m_tokenExpires;

    QThread m_threadAuthBrowser;
    std::unique_ptr<AuthenticationGui> m_authBrowser;
    std::unique_ptr<QTcpServer> m_tcpServer;
};

