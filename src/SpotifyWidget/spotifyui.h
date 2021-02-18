#pragma once

#include <QWidget>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <memory>

#include <spotify.h>
#include <playlist/playlists.h>
#include <playlist/track.h>

namespace Ui {
class SpotifyUI;
}

class SpotifyUI : public QWidget
{
    Q_OBJECT

public:
    explicit SpotifyUI(QWidget *parent = nullptr);
    ~SpotifyUI();

private slots:
    void on_buttonSearch_clicked();
    void on_buttonAddMusic_clicked();

    void updateComboPlaylist();
    void updateListTracksPlaylist(int index);

    void on_buttonRemovePlaylist_clicked();
    void on_buttonRemoveMusic_clicked();
    void on_buttonPlayPlaylist_clicked();
    void on_buttonPlayPause_clicked();
    void on_buttonStop_clicked();
    void on_buttonPrevious_clicked();
    void on_buttonNext_clicked();

    void configurePlayer();

private:
    Ui::SpotifyUI *ui;
    std::unique_ptr<Spotify> m_spotify;
    std::unique_ptr<Playlists> m_playlists;
    std::unique_ptr<QMediaPlaylist> m_playlist;
    std::unique_ptr<QMediaPlayer> m_mediaPlayer;

    QVariantList m_resultSearch;
    QVariantList m_queue;
};
