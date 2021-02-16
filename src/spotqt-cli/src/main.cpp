#include <QGuiApplication>
#include <QtWebEngine/qtwebengineglobal.h>
#include <QTimer>
#include <QDebug>
#include <memory>

#include <authentication/authenticationservice.h>
#include <spotqt.h>

int main(int argc, char *argv[])
{
    QtWebEngine::initialize();
    QGuiApplication a(argc, argv);

    std::unique_ptr<AuthenticationService> authService = std::make_unique<AuthenticationService>();
    if (authService->needToAuthenticate()) {
        authService->setClientId(QStringLiteral("f8023ea988e548df83fb42b5ce1e1a20"));
        authService->setClientSecret(QStringLiteral("5cf01313067d4391a9a8643add01307a"));

        authService->startAuthenticationService();
    }

    qDebug() << "Spotify API - CLI";

    return QGuiApplication::exec();
}
