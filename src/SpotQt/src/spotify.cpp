#include "spotify.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Spotify::Spotify(QObject *parent) :
    QObject(parent),
    m_authService(std::make_unique<AuthenticationService>()),
    m_settings(std::make_unique<Settings>()),
    m_eventLoop(std::make_unique<QEventLoop>()),
    m_authenticated(false)
{
    m_settings->loadAll(*m_settings);

    m_authService->setClientId(m_settings->getItemSettings(Settings::Type::ClientID)->value().toString());
    m_authService->setClientSecret(m_settings->getItemSettings(Settings::Type::ClientSecret)->value().toString());
    m_authService->setUserToken(m_settings->getItemSettings(Settings::Type::UserToken)->value().toString());
    m_authService->setTokenExpires(m_settings->getItemSettings(Settings::Type::TokenExpires)->value().toDateTime());

    connect(m_authService.get(), &AuthenticationService::authenticated, this, [&]() { setAuthenticated(true); });
    connect(m_authService.get(), &AuthenticationService::authenticationFailed, this, [&]() { setAuthenticated(false); });

    tokenIsValid();
}

bool Spotify::authenticated() const
{
    return m_authenticated;
}

void Spotify::setAuthenticated(bool authenticated)
{
    if (m_authenticated == authenticated)
        return;

    m_authenticated = authenticated;
    emit authenticatedChanged();
}

QVariantList Spotify::searchMusic(const QString &type)
{
    tokenIsValid();

    QNetworkAccessManager networkManager;
    auto *reply = networkManager.get(spotifyRequest(QStringLiteral("search?q=%1&type=track").arg(type)));

    QEventLoop eventLoop;
    connect(&networkManager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() != QNetworkReply::NoError)
        qCritical() << "Error trying request" << reply->error() << reply->errorString();

    try {
        QJsonParseError parseError{};
        auto json = QJsonDocument::fromJson(reply->readAll(), &parseError);
        if (parseError.error != QJsonParseError::NoError)
            qCritical() << "Error trying to parse JSON" << parseError.errorString();

        const auto &tracks = json.object().value(QStringLiteral("tracks")).toObject().toVariantMap()[QStringLiteral("items")].toList();
        return searchTracks(tracks);
    }  catch (...) {
        qCritical() << "Error trying read message";
    }

    return {};
}

QNetworkRequest Spotify::spotifyRequest(const QString &uri)
{
    QUrl url(QStringLiteral("https://api.spotify.com/v1/%1").arg(uri));
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", QStringLiteral("Bearer %1").arg(m_authService->getUserToken()).toUtf8());
    return request;
}

QVariantList Spotify::searchTracks(const QVariantList &tracks)
{
    QVariantList list;

    for (const auto &track: tracks) {
        const auto &map = track.toMap();

        if (map[QStringLiteral("preview_url")].toString().isEmpty())
            continue;

        list << QVariantMap({
                                { "name", map[QStringLiteral("name")].toString() },
                                { "previewUrl", map[QStringLiteral("preview_url")].toString() },
                                { "artist", map[QStringLiteral("artists")].toList().at(0).toMap()[QStringLiteral("name")].toString() },
                                { "image", map[QStringLiteral("album")].toMap()[QStringLiteral("images")].toList().last().toMap()[QStringLiteral("url")].toString() }
                            });
    }

    qDebug().noquote() << QJsonDocument::fromVariant(list).toJson(QJsonDocument::Indented);

    return list;
}

void Spotify::tokenIsValid()
{
    if (m_authService->needAuthentication()) {
        m_authService->startAuthenticationService();
        connect(m_authService.get(), &AuthenticationService::authorizationCodeChanged, m_authService.get(), &AuthenticationService::getSpotifyToken);
        connect(m_authService.get(), &AuthenticationService::authenticationChanged, [&]()
        {
            auto *userToken = m_settings->getItemSettings(Settings::Type::UserToken);
            auto *tokenExpires = m_settings->getItemSettings(Settings::Type::TokenExpires);

            userToken->setValue(m_authService->getUserToken());
            tokenExpires->setValue(m_authService->getTokenExpires());
            m_settings->updateItems();
        });

        connect(m_authService.get(), &AuthenticationService::authenticated, this, [&]() { m_eventLoop->quit(); });
        connect(m_authService.get(), &AuthenticationService::authenticationFailed, this, [&]() { m_eventLoop->quit(); });
        m_eventLoop->exec();
    }
}
