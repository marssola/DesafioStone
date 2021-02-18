#pragma once

#include <QObject>
#include <QMap>
#include "playlistdao.h"

class Track;

class Playlists : public QObject
{
    Q_PROPERTY(int size READ getSize NOTIFY playlistsChanged)
    Q_OBJECT
public:
    explicit Playlists(QObject *parent = nullptr);
    ~Playlists();

    QList<Track *> getPlaylists();

    void clear();
    int getSize();

public slots:
    void addPlaylist(Track *playlist, bool notifyChanged = true);
    void removePlaylist(const QString &playlistName);
    void removeTrack(int index, const QString &playlistName);

    bool loadAll(Playlists *playlists);

    int getNextTrackId() const;

    QList<Track *> getPlaylist(const QString &playlistName);
    QStringList getPlaylistsName() const;

signals:
    void playlistsChanged();

private:
    QList<Track *> m_playlists;
    PlaylistDao m_playlistDao;
    int m_nextTrackId;
};

