#include <QGuiApplication>
#include <QtWebEngine/qtwebengineglobal.h>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <memory>

#include <authentication/authenticationservice.h>
#include <settings/settings.h>

int main(int argc, char *argv[])
{
    QtWebEngine::initialize();
    QGuiApplication a(argc, argv);

    std::unique_ptr<Settings> settings =  std::make_unique<Settings>();
    std::unique_ptr<AuthenticationService> authService = std::make_unique<AuthenticationService>();

    settings->loadAll(*settings);

    authService->setClientId(settings->getItemSettings(Settings::Type::ClientID)->value().toString());
    authService->setClientSecret(settings->getItemSettings(Settings::Type::ClientSecret)->value().toString());
    authService->setUserToken(settings->getItemSettings(Settings::Type::UserToken)->value().toString());
    authService->setTokenExpires(settings->getItemSettings(Settings::Type::TokenExpires)->value().toDateTime());

    QObject::connect(authService.get(), &AuthenticationService::authenticated, [&]() {
        qDebug() << "Autenticado";
    });

    if (authService->needAuthentication()) {
        authService->startAuthenticationService();
        QObject::connect(authService.get(), &AuthenticationService::authorizationCodeChanged, authService.get(), &AuthenticationService::getSpotifyToken);
        QObject::connect(authService.get(), &AuthenticationService::authenticationChanged, [&]() {
            auto *userToken = settings->getItemSettings(Settings::Type::UserToken);
            auto *tokenExpires = settings->getItemSettings(Settings::Type::TokenExpires);

            userToken->setValue(authService->getUserToken());
            tokenExpires->setValue(authService->getTokenExpires());
            settings->updateItems();
        });
    }

    qDebug() << "Spotify API - CLI";

    return QGuiApplication::exec();
}
