#include <QGuiApplication>
#include <QtWebEngine/qtwebengineglobal.h>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <memory>

#include <QJsonDocument>

#include <spotify.h>

int main(int argc, char *argv[])
{
    QtWebEngine::initialize();
    QGuiApplication a(argc, argv);

    Spotify spotifyClient;
    const auto search1 = spotifyClient.searchMusic(QStringLiteral("Children of the sea"));
    const auto search2 = spotifyClient.searchMusic(QStringLiteral("Children of the grave"));
    const auto search3 = spotifyClient.searchMusic(QStringLiteral("Beat the Basterds"));
    const auto search4 = spotifyClient.searchMusic(QStringLiteral("Natural Science"));

    qDebug().noquote() << QJsonDocument::fromVariant(search1.at(0).toMap()).toJson(QJsonDocument::Indented);
    qDebug().noquote() << QJsonDocument::fromVariant(search2.at(0).toMap()).toJson(QJsonDocument::Indented);
    qDebug().noquote() << QJsonDocument::fromVariant(search3.at(0).toMap()).toJson(QJsonDocument::Indented);
    qDebug().noquote() << QJsonDocument::fromVariant(search4.at(0).toMap()).toJson(QJsonDocument::Indented);

    qDebug() << "Spotify API - CLI";

    return QGuiApplication::exec();
}
