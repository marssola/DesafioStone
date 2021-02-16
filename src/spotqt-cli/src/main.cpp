#include <QGuiApplication>
#include <QtWebEngine/qtwebengineglobal.h>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <memory>

#include <spotify.h>

int main(int argc, char *argv[])
{
    QtWebEngine::initialize();
    QGuiApplication a(argc, argv);

    Spotify spotifyClient;
    spotifyClient.searchMusic(QStringLiteral("Children of the sear"));

    qDebug() << "Spotify API - CLI";

    return QGuiApplication::exec();
}
