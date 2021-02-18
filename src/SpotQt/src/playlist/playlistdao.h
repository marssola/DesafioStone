#pragma once

#include "../database/abstractdao.h"
#include <QString>

class Playlists;

class PlaylistDao : public AbstractDao
{
    const QString m_table;

public:
    PlaylistDao();

    bool loadAll(Playlists *playlists);

private:
    void createTable() override;

    bool readData(QSqlQuery &query, Playlists *playlists);

    QString getQueryStr(TypeQuery type);
};

