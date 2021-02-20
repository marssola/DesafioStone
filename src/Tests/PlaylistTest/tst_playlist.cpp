#include <QtTest>

// add necessary includes here
#include <playlist/track.h>
#include <playlist/playlists.h>
#include <playlist/playlistdao.h>

class PlaylistTest : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(PlaylistTest)

    Playlists m_playlist;
    PlaylistDao m_playlistsDao;

public:
    PlaylistTest() = default;
    ~PlaylistTest() override = default;

private slots:
    void initTestCase();

    void loadTracks();
    void totalRegisters();
    void removeOneTrack();
    void removePlaylist();
    void totalTracksAfterDelete();
};

void PlaylistTest::initTestCase()
{
    Track *track1 = new Track;
    track1->setId(1);
    track1->setPlaylistName(QStringLiteral("Madman"));
    track1->setTrack(QStringLiteral("Crazy Train"));
    track1->setArtist(QStringLiteral("Ozzy Osbourne"));
    track1->setPreviewUrl(QStringLiteral("https://p.scdn.co/mp3-preview/895ade6bcec3f39ce53665e77d8ca6e20f754fe1?cid=f8023ea988e548df83fb42b5ce1e1a20"));
    track1->setImage(QStringLiteral("https://i.scdn.co/image/ab67616d00004851475ca6e5c1ce0ef70740c3c6"));

    Track *track2 = new Track;
    track2->setId(2);
    track2->setPlaylistName(QStringLiteral("Madman"));
    track2->setTrack(QStringLiteral("Mr. Crowley"));
    track2->setArtist(QStringLiteral("Ozzy Osbourne"));
    track2->setPreviewUrl(QStringLiteral("https://p.scdn.co/mp3-preview/592fab429bc7a84d1900a0e98cfc44192610842a?cid=f8023ea988e548df83fb42b5ce1e1a20"));
    track2->setImage(QStringLiteral("https://i.scdn.co/image/ab67616d00004851475ca6e5c1ce0ef70740c3c6"));

    Track *track3 = new Track;
    track3->setId(3);
    track3->setPlaylistName(QStringLiteral("Madman"));
    track3->setTrack(QStringLiteral("The Ultimate Sin"));
    track3->setArtist(QStringLiteral("Ozzy Osbourne"));
    track3->setPreviewUrl(QStringLiteral("https://p.scdn.co/mp3-preview/ce7de55167dffa80a926089be6dbd4be48db68e6?cid=f8023ea988e548df83fb42b5ce1e1a20"));
    track3->setImage(QStringLiteral("https://i.scdn.co/image/ab67616d00004851c8dec214036a4cfb3dcf143a"));

    Track *track4 = new Track;
    track4->setId(4);
    track4->setPlaylistName(QStringLiteral("Madman"));
    track4->setTrack(QStringLiteral("Killer of Giants"));
    track4->setArtist(QStringLiteral("Ozzy Osbourne"));
    track4->setPreviewUrl(QStringLiteral("https://p.scdn.co/mp3-preview/0c5126a6db81706d97c00f26a42ed3d3b86c3ac7?cid=f8023ea988e548df83fb42b5ce1e1a20"));
    track4->setImage(QStringLiteral("https://i.scdn.co/image/ab67616d00004851c8dec214036a4cfb3dcf143a"));

    m_playlistsDao.addTrack(track1);
    m_playlistsDao.addTrack(track2);
    m_playlistsDao.addTrack(track3);
    m_playlistsDao.addTrack(track4);
}

void PlaylistTest::loadTracks()
{
    QVERIFY(m_playlistsDao.loadAll(&m_playlist));
}

void PlaylistTest::totalRegisters()
{
    QVERIFY(m_playlist.getSize() == 4);
}

void PlaylistTest::removeOneTrack()
{
    QVERIFY(m_playlistsDao.removeTrack(m_playlist.getPlaylists().at(0)));
}

void PlaylistTest::removePlaylist()
{
    QVERIFY(m_playlistsDao.removePlaylist(QStringLiteral("Madman")));
}

void PlaylistTest::totalTracksAfterDelete()
{
    m_playlistsDao.loadAll(&m_playlist);
    QVERIFY(m_playlist.getSize() == 0);
}

QTEST_APPLESS_MAIN(PlaylistTest)

#include "tst_playlist.moc"
