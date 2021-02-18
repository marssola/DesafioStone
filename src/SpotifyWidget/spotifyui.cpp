#include "spotifyui.h"
#include "ui_spotifyui.h"

#include <playlist/track.h>
#include <QInputDialog>
#include <QMessageBox>
#include <QVariantMap>
#include <QDebug>

SpotifyUI::SpotifyUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpotifyUI),
    m_spotify(std::make_unique<Spotify>()),
    m_playlists(std::make_unique<Playlists>()),
    m_playlist(std::make_unique<QMediaPlaylist>()),
    m_mediaPlayer(std::make_unique<QMediaPlayer>())
{
    ui->setupUi(this);
    ui->buttonSearch->setEnabled(!ui->fieldSearch->text().isEmpty());
    ui->buttonAddMusic->setEnabled(ui->listWidget->count() > 0);
    ui->buttonRemoveMusic->setEnabled(ui->listPlaylist->count() > 0);
    ui->buttonRemovePlaylist->setEnabled(ui->comboPlaylists->currentIndex() > -1);
    ui->buttonPlayPlaylist->setEnabled(ui->comboPlaylists->currentIndex() > -1);

    connect(ui->comboPlaylists, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&](int index)
    {
        updateListTracksPlaylist(index);
        ui->buttonRemovePlaylist->setEnabled(index > -1);
        ui->buttonPlayPlaylist->setEnabled(index > -1);
    });
    connect(ui->fieldSearch, &QLineEdit::textChanged, this, [&]() { ui->buttonSearch->setEnabled(!ui->fieldSearch->text().isEmpty()); });
    connect(ui->listWidget, &QListWidget::currentRowChanged, this, [&](int currentRow) { ui->buttonAddMusic->setEnabled(currentRow > -1); });
    connect(ui->listPlaylist, &QListWidget::currentRowChanged, this, [&](int currentRow) { ui->buttonRemoveMusic->setEnabled(currentRow > -1); });

    connect(m_playlists.get(), &Playlists::playlistsChanged, this, &SpotifyUI::updateComboPlaylist);
    connect(m_playlists.get(), &Playlists::error, this, [&](const QString &msg) { QMessageBox::critical(this, QStringLiteral("Error"), msg, QMessageBox::Ok); });

    connect(m_playlist.get(), &QMediaPlaylist::currentIndexChanged, this, &SpotifyUI::configurePlayer);
    connect(m_mediaPlayer.get(), &QMediaPlayer::positionChanged, ui->progessMusic, &QProgressBar::setValue);
    connect(m_mediaPlayer.get(), &QMediaPlayer::durationChanged, ui->progessMusic, &QProgressBar::setMaximum);
    connect(m_mediaPlayer.get(), &QMediaPlayer::stateChanged, this, [&]()
    {
        switch (m_mediaPlayer->state()) {
        case QMediaPlayer::StoppedState: ui->buttonPlayPause->setText(QStringLiteral("Play")); break;
        case QMediaPlayer::PlayingState: ui->buttonPlayPause->setText(QStringLiteral("Pause")); break;
        case QMediaPlayer::PausedState: ui->buttonPlayPause->setText(QStringLiteral("Play")); break;
        }
    });

    configurePlayer();
    m_playlists->loadAll(m_playlists.get());
}

SpotifyUI::~SpotifyUI()
{
    delete ui;
}

void SpotifyUI::on_buttonSearch_clicked()
{
    ui->listWidget->clear();
    m_resultSearch.clear();
    m_resultSearch = m_spotify->searchMusic(ui->fieldSearch->text());

    for (auto &track : m_resultSearch) {
        const auto &mapTrack = track.toMap();

        ui->listWidget->addItem(QStringLiteral("%1 - %2").arg(
                                    mapTrack[QStringLiteral("artist")].toString(),
                                    mapTrack[QStringLiteral("name")].toString()
                                ));
    }
}

void SpotifyUI::on_buttonAddMusic_clicked()
{
    bool ok = false;
    auto playlistsNames = m_playlists->getPlaylistsName();
    const QString playlistName = QInputDialog::getItem(this,
                                                       QStringLiteral("Playlist"),
                                                       QStringLiteral("Add to Playlist"),
                                                       playlistsNames, -1,
                                                       true, &ok);

    if (!ok)
        return;

    if (playlistName.isEmpty()) {
        QMessageBox msg;
        msg.setText(QStringLiteral("No playlist was selected"));
        msg.exec();
        return;
    }

    const auto &choose = m_resultSearch.at(ui->listWidget->currentIndex().row()).toMap();

    auto *track = new Track;
    track->setId(m_playlists->getNextTrackId());
    track->setPlaylistName(playlistName);
    track->setTrack(choose[QStringLiteral("name")].toString());
    track->setArtist(choose[QStringLiteral("artist")].toString());
    track->setPreviewUrl(choose[QStringLiteral("previewUrl")].toString());
    track->setImage(choose[QStringLiteral("image")].toString());

    m_playlists->addPlaylist(track);
}

void SpotifyUI::updateComboPlaylist()
{
    ui->comboPlaylists->clear();
    ui->comboPlaylists->addItems(m_playlists->getPlaylistsName());
}

void SpotifyUI::updateListTracksPlaylist(int /*index*/)
{
    ui->listPlaylist->clear();

    const auto &playlist = m_playlists->getPlaylist(ui->comboPlaylists->currentText());
    for (const auto &track : playlist) {
        ui->listPlaylist->addItem(QStringLiteral("%1 - %2").arg(track->getArtist(), track->getTrack()));
    }
}

void SpotifyUI::on_buttonRemovePlaylist_clicked()
{
    QMessageBox msg;
    msg.setText(QStringLiteral("Do you really want to remove this playlist?"));
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);

    switch (msg.exec()) {
    case QMessageBox::Yes:
        m_playlists->removePlaylist(ui->comboPlaylists->currentText());
        break;
    default:
        break;
    }
}

void SpotifyUI::on_buttonRemoveMusic_clicked()
{
    QMessageBox msg;
    msg.setText(QStringLiteral("Do you really want to remove this track?"));
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);

    switch (msg.exec()) {
    case QMessageBox::Yes:
        m_playlists->removeTrack(ui->listPlaylist->currentIndex().row(), ui->comboPlaylists->currentText());
        break;
    default:
        break;
    }
}

void SpotifyUI::on_buttonPlayPlaylist_clicked()
{
    m_playlist->clear();

    m_queue = m_playlists->getPlaylistToQueue(ui->comboPlaylists->currentText());
    for (auto &track : m_queue) {
        m_playlist->addMedia(QUrl(track.toMap()[QStringLiteral("previewUrl")].toString()));
    }

    m_playlist->setObjectName(ui->comboPlaylists->currentText());
    m_playlist->setCurrentIndex(0);
    m_mediaPlayer->setPlaylist(m_playlist.get());
}

void SpotifyUI::on_buttonPlayPause_clicked()
{
    switch (m_mediaPlayer->state()) {
    case QMediaPlayer::StoppedState: m_mediaPlayer->play(); break;
    case QMediaPlayer::PlayingState: m_mediaPlayer->pause(); break;
    case QMediaPlayer::PausedState: m_mediaPlayer->play(); break;
    }
}

void SpotifyUI::on_buttonStop_clicked()
{
    m_mediaPlayer->stop();
}

void SpotifyUI::on_buttonPrevious_clicked()
{
    m_playlist->previous();
}

void SpotifyUI::on_buttonNext_clicked()
{
    m_playlist->next();
}

void SpotifyUI::configurePlayer()
{
    const auto index = m_playlist->currentIndex();
    ui->buttonPlayPause->setEnabled(index > -1);
    ui->buttonStop->setEnabled(index > -1);
    ui->buttonPrevious->setEnabled(index > -1);
    ui->buttonNext->setEnabled(index > -1);

    if (index < 0) {
        ui->labelMediaPlayer->setText(QStringLiteral("No playlist defined"));
        m_queue.clear();
        return;
    }

    auto playlist = m_queue[index].toMap();
    ui->labelMediaPlayer->setText(QStringLiteral(" Playlist: %1 - Track: %2").arg(m_playlist->objectName(), playlist[QStringLiteral("track")].toString()));
}
