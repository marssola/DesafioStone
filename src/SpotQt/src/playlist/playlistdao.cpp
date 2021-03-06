#include "playlistdao.h"
#include "playlists.h"
#include "track.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

PlaylistDao::PlaylistDao() :
    m_table(QStringLiteral("playlist"))
{
    createTable();
}

bool PlaylistDao::loadAll(Playlists *playlists)
{
    if (!openConnection()) {
        qCritical() << "Error trying open connection database" << getConnection().lastError().text();
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(getQueryStr(TypeQuery::All));
    return readData(query, playlists);
}

bool PlaylistDao::addTrack(Track *track)
{
    if (!openConnection()) {
        qCritical() << "Error trying open connection database" << getConnection().lastError().text();
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("INSERT OR REPLACE INTO %1 (id, playlistName, track, artist, previewUrl, image) VALUES(:id, :playlistName, :track, :artist, :previewUrl, :image)").arg(m_table));
    query.bindValue(QStringLiteral(":id"), track->getId());
    query.bindValue(QStringLiteral(":playlistName"), track->getPlaylistName());
    query.bindValue(QStringLiteral(":track"), track->getTrack());
    query.bindValue(QStringLiteral(":artist"), track->getArtist());
    query.bindValue(QStringLiteral(":previewUrl"), track->getPreviewUrl());
    query.bindValue(QStringLiteral(":image"), track->getImage());

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Error trying insert new track" << query.lastError().text();

    closeConnection();
    return exec;
}

bool PlaylistDao::removeTrack(Track *track)
{
    if (!openConnection()) {
        qCritical() << "Error trying open connection database" << getConnection().lastError().text();
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("DELETE FROM %1 WHERE id=:id").arg(m_table));
    query.bindValue(QStringLiteral(":id"), track->getId());

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Error trying remove new track" << query.lastError().text();

    closeConnection();
    return exec;
}

bool PlaylistDao::removePlaylist(const QString &playlistName)
{
    if (!openConnection()) {
        qCritical() << "Error trying open connection database" << getConnection().lastError().text();
        return false;
    }

    QSqlQuery query(getConnection());
    query.prepare(QStringLiteral("DELETE FROM %1 WHERE playlistName=:playlistName").arg(m_table));
    query.bindValue(QStringLiteral(":playlistName"), playlistName);

    const auto exec = query.exec();
    if (!exec)
        qCritical() << "Error trying remove new track" << query.lastError().text();

    closeConnection();
    return exec;
}

void PlaylistDao::createTable()
{
    if (!openConnection()) {
        qCritical() << "Error trying open database" << getConnection().lastError().text();
        return;
    }

    const QString createTableStr(QStringLiteral("CREATE TABLE IF NOT EXISTS %1 ("
            "id INTEGER UNIQUE,"
            "playlistName TEXT,"
            "track TEXT,"
            "artist TEXT,"
            "previewUrl TEXT,"
            "image TEXT,"
            "PRIMARY KEY(id)"
        ");").arg(m_table));

    QSqlQuery query(getConnection());
    query.prepare(createTableStr);

    if (!query.exec())
        qCritical() << "Error trying create database" << query.lastError().text() << query.lastQuery();

    closeConnection();
}

bool PlaylistDao::readData(QSqlQuery &query, Playlists *playlists)
{
    const bool exec = query.exec();
    if (!exec) {
        qCritical() << "Error trying read data" << query.lastError().text();
    } else {
        constexpr auto fieldId = 0;
        constexpr auto fieldPlaylistName = 1;
        constexpr auto fieldTrack = 2;
        constexpr auto fieldArtist = 3;
        constexpr auto fieldPreviewUrl = 4;
        constexpr auto fieldImage = 5;

        playlists->clear();
        while (query.next()) {
            Track *track = new Track;

            track->setId(query.value(fieldId).toInt());
            track->setPlaylistName(query.value(fieldPlaylistName).toString());
            track->setTrack(query.value(fieldTrack).toString());
            track->setArtist(query.value(fieldArtist).toString());
            track->setPreviewUrl(query.value(fieldPreviewUrl).toString());
            track->setImage(query.value(fieldImage).toString());

            playlists->addPlaylist(track, false, false);

        }
        emit playlists->playlistsChanged();
    }

    closeConnection();
    return exec;
}

QString PlaylistDao::getQueryStr(AbstractDao::TypeQuery type)
{
    QString queryStr(QStringLiteral("SELECT"));
    switch (type) {
    case TypeQuery::All:
        queryStr += QStringLiteral(" id, playlistName, track, artist, previewUrl, image");
        break;
    }
    queryStr += QStringLiteral(" FROM %1").arg(m_table);

    return queryStr;
}
