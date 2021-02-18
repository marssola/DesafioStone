#include "track.h"

Track::Track(QObject *parent) :
    QObject(parent),
    m_id(0),
    m_playlistName(QStringLiteral("")),
    m_track(QStringLiteral("")),
    m_artist(QStringLiteral("")),
    m_previewUrl(QStringLiteral("")),
    m_image(QStringLiteral(""))
{}

int Track::getId() const
{
    return m_id;
}

QString Track::getPlaylistName() const
{
    return m_playlistName;
}

QString Track::getTrack() const
{
    return m_track;
}

QString Track::getPreviewUrl() const
{
    return m_previewUrl;
}

QString Track::getImage() const
{
    return m_image;
}

QString Track::getArtist() const
{
    return m_artist;
}

void Track::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged();
}

void Track::setPlaylistName(const QString& name)
{
    if (m_playlistName == name)
        return;

    m_playlistName = name;
    emit playlistNameChanged();
}

void Track::setTrack(const QString& track)
{
    if (m_track == track)
        return;

    m_track = track;
    emit trackChanged();
}

void Track::setPreviewUrl(const QString& previewUrl)
{
    if (m_previewUrl == previewUrl)
        return;

    m_previewUrl = previewUrl;
    emit previewUrlChanged();
}

void Track::setImage(const QString &image)
{
    if (m_image == image)
        return;

    m_image = image;
    emit imageChanged();
}

void Track::setArtist(const QString &artist)
{
    if (m_artist == artist)
        return;

    m_artist = artist;
    emit artistChanged();
}
