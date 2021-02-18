#pragma once

#include <QWidget>
#include <memory>

#include <spotify.h>
#include <playlist/playlists.h>

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

private:
    Ui::SpotifyUI *ui;
    std::unique_ptr<Spotify> m_spotify;
    std::unique_ptr<Playlists> m_playlists;

    QVariantList m_resultSearch;
};
