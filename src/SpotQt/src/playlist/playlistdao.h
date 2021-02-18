#pragma once

#include "../database/abstractdao.h"
#include <QString>

class Track;
class Playlists;

class PlaylistDao : public AbstractDao
{
    const QString m_table;

public:
    PlaylistDao();

    bool loadAll(Playlists *playlists);

    bool addTrack(Track *track);

    bool removeTrack(Track *track);

    bool removePlaylist(const QString &playlistName);

private:
    void createTable() override;

    bool readData(QSqlQuery &query, Playlists *playlists);

    QString getQueryStr(TypeQuery type);
};

