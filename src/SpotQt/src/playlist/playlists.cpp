#include "playlists.h"
#include "track.h"

#include <algorithm>

Playlists::Playlists(QObject *parent) :
    QObject(parent),
    m_nextTrackId(1)
{}

Playlists::~Playlists()
{
    clear();
}

QList<Track *> Playlists::getPlaylists()
{
    return m_playlists;
}

void Playlists::clear()
{
    std::for_each(std::begin(m_playlists), std::end(m_playlists), [](Track *item) { delete item; });
    m_playlists.clear();
}

int Playlists::getSize()
{
    return m_playlists.size();
}

void Playlists::addPlaylist(Track *playlist, bool notifyChanged)
{
    m_playlists.append(playlist);
    if (playlist->getId() >= m_nextTrackId)
        m_nextTrackId = playlist->getId() + 1;

    if (notifyChanged)
        emit playlistsChanged();
}

void Playlists::removePlaylist(const QString &playlistName)
{
    for (auto it = std::begin(m_playlists); it != std::end(m_playlists); ++it) {
        if (it.i->t()->getPlaylistName() == playlistName) {
            m_playlists.removeOne(it.i->t());
            delete it.i->t();
        }
    }
    emit playlistsChanged();
}

void Playlists::removeTrack(int index, const QString &playlistName)
{
    auto playlist = getPlaylist(playlistName);
    m_playlists.removeOne(playlist[index]);

    delete playlist[index];
    emit playlistsChanged();
}

bool Playlists::loadAll(Playlists *playlists)
{
    return m_playlistDao.loadAll(playlists);
}

int Playlists::getNextTrackId() const
{
    return m_nextTrackId;
}

QList<Track *> Playlists::getPlaylist(const QString &playlistName)
{
    QList<Track *> playlist;
    std::for_each(std::begin(m_playlists), std::end(m_playlists), [&playlistName, &playlist](Track *item)
    {
        if (item->getPlaylistName() == playlistName)
            playlist.append(item);
    });
    return playlist;
}

QStringList Playlists::getPlaylistsName() const
{
    QStringList names;
    std::for_each(std::begin(m_playlists), std::end(m_playlists), [&names](Track *item) { if (!names.contains(item->getPlaylistName())) names.append(item->getPlaylistName()); });
    return names;
}
