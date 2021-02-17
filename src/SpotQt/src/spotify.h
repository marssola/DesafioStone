#pragma once

#include <QObject>
#include <QNetworkRequest>
#include <QEventLoop>
#include <memory>

#include "authentication/authenticationservice.h"
#include "settings/settings.h"

class Spotify : public QObject
{
    Q_PROPERTY(bool authenticated READ authenticated WRITE setAuthenticated NOTIFY authenticatedChanged)
    Q_OBJECT
public:
    explicit Spotify(QObject *parent = nullptr);

    bool authenticated() const;
    void setAuthenticated(bool authenticated);

public slots:
    QVariantList searchMusic(const QString &type);

private slots:
    void tokenIsValid();
    QNetworkRequest spotifyRequest(const QString &uri);
    static QVariantList searchTracks(const QVariantList &tracks);

signals:
    void authenticatedChanged();

private:
    std::unique_ptr<AuthenticationService> m_authService;
    std::unique_ptr<Settings> m_settings;
    std::unique_ptr<QEventLoop> m_eventLoop;

    bool m_authenticated;
};

