#include "playlists.h"
#include "track.h"

#include <QVariantMap>
#include <algorithm>

#include <QJsonDocument>
#include <QDebug>

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

Track *Playlists::createTrack(const QVariantMap &track) const
{
    auto *newTrack = new Track;

    newTrack->setId(getNextTrackId());
    newTrack->setTrack(track[QStringLiteral("name")].toString());
    newTrack->setPlaylistName(track[QStringLiteral("playlistName")].toString());
    newTrack->setArtist(track[QStringLiteral("artist")].toString());
    newTrack->setPreviewUrl(track[QStringLiteral("previewUrl")].toString());
    newTrack->setImage(track[QStringLiteral("image")].toString());

    return newTrack;
}

void Playlists::addPlaylist(Track *track, bool notifyChanged, bool updateDb)
{
    if (updateDb && !m_playlistDao.addTrack(track)) {
        emit error(QStringLiteral("There was an error inserting the track into the playlist"));
        return;
    }

    m_playlists.append(track);
    if (track->getId() >= m_nextTrackId)
        m_nextTrackId = track->getId() + 1;

    if (notifyChanged)
        emit playlistsChanged();
}

void Playlists::removePlaylist(const QString &playlistName)
{
    if (!m_playlistDao.removePlaylist(playlistName)) {
        emit error(QStringLiteral("There was an error removing playlist"));
        return;
    }

    loadAll(this);
}

void Playlists::removeTrack(int index, const QString &playlistName)
{
    auto playlist = getPlaylist(playlistName);
    auto *track = playlist[index];

    if (!m_playlistDao.removeTrack(track)) {
        emit error(QStringLiteral("There was an error removing the track from the playlist"));
        return;
    }

    m_playlists.removeOne(track);
    delete track;
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

QVariantList Playlists::getPlaylistByName(const QString &playlistName) const
{
    QVariantList playlist;
    std::for_each(std::begin(m_playlists), std::end(m_playlists), [&playlistName, &playlist](Track *item)
    {
        if (item->getPlaylistName() == playlistName)
            playlist << QVariantMap({
                                        { "id", item->getId() },
                                        { "playlistName", item->getPlaylistName() },
                                        { "track", item->getTrack() },
                                        { "artist", item->getArtist() },
                                        { "previewUrl", item->getPreviewUrl() },
                                        { "image", item->getImage() },
                                    });
    });
    return playlist;
}

QVariantList Playlists::getPlaylistToQueue(const QString &playlistName)
{
    QVariantList list;
    std::for_each(std::begin(m_playlists), std::end(m_playlists), [&playlistName, &list](Track *item)
    {
        if (item->getPlaylistName() == playlistName)
            list << QVariantMap({
                                    { "playlistName", item->getPlaylistName() },
                                    { "track", item->getTrack() },
                                    { "artist", item->getArtist() },
                                    { "previewUrl", item->getPreviewUrl() },
                                    { "image", item->getImage() },
                                });
    });

    return list;
}

QStringList Playlists::getPlaylistsName() const
{
    QStringList names;
    std::for_each(std::begin(m_playlists), std::end(m_playlists), [&names](Track *item) { if (!names.contains(item->getPlaylistName())) names.append(item->getPlaylistName()); });
    return names;
}

QStringList Playlists::imagesFromPlaylist(const QString playlistName) const
{
    QStringList images;
    std::for_each(std::begin(m_playlists), std::end(m_playlists), [&playlistName, &images](Track *item)
    {
        if (item->getPlaylistName() == playlistName && images.indexOf(item->getImage()) < 0)
            images << item->getImage();
    });
    return images;
}
