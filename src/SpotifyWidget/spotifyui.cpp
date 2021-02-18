#include "spotifyui.h"
#include "ui_spotifyui.h"

#include <playlist/track.h>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

SpotifyUI::SpotifyUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpotifyUI),
    m_spotify(std::make_unique<Spotify>()),
    m_playlists(std::make_unique<Playlists>()),
    m_newPlaylist(QStringLiteral(""))
{
    ui->setupUi(this);
    ui->buttonSearch->setEnabled(!ui->fieldSearch->text().isEmpty());
    ui->buttonAddMusic->setEnabled(ui->listWidget->count() > 0);
    ui->buttonRemoveMusic->setEnabled(ui->listPlaylist->count() > 0);
    ui->buttonRemovePlaylist->setEnabled(ui->comboPlaylists->currentIndex() > -1);

    connect(ui->fieldSearch, &QLineEdit::textChanged, this, [&]() { ui->buttonSearch->setEnabled(!ui->fieldSearch->text().isEmpty()); });
    connect(ui->comboPlaylists, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&](int index)
    {
        updateListTracksPlaylist(index);
        ui->buttonRemovePlaylist->setEnabled(index > -1);
    });
    connect(m_playlists.get(), &Playlists::playlistsChanged, this, &SpotifyUI::updateComboPlaylist);

    connect(ui->listWidget, &QListWidget::currentRowChanged, this, [&](int currentRow) { ui->buttonAddMusic->setEnabled(currentRow > -1); });
    connect(ui->listPlaylist, &QListWidget::currentRowChanged, this, [&](int currentRow) { ui->buttonRemoveMusic->setEnabled(currentRow > -1); });

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
    auto playlistsNames = m_playlists->getPlaylistsName();
    if (!playlistsNames.contains(m_newPlaylist))
        playlistsNames.append(m_newPlaylist);

    bool ok = false;
    const QString playlistName = QInputDialog::getItem(this,
                                                       QStringLiteral("Playlist"),
                                                       QStringLiteral("Add to Playlist"),
                                                       playlistsNames, -1,
                                                       false, &ok);

    if (!ok)
        return;

    if (playlistName.isEmpty()) {
        QMessageBox msg;
        msg.setText(QStringLiteral("No playlist was selected"));
        msg.exec();
        return;
    }

    const auto &choose = m_resultSearch.at(ui->listWidget->currentIndex().row()).toMap();

    Track *track = new Track;
    track->setId(m_playlists->getNextTrackId());
    track->setPlaylistName(playlistName);
    track->setTrack(choose[QStringLiteral("name")].toString());
    track->setArtist(choose[QStringLiteral("artist")].toString());
    track->setPreviewUrl(choose[QStringLiteral("previewUrl")].toString());
    track->setImage(choose[QStringLiteral("image")].toString());

    m_playlists->addPlaylist(track);
}

void SpotifyUI::on_buttonNewPlaylist_clicked()
{
    bool ok = false;
    const QString playlistName = QInputDialog::getText(this,
                                                       QStringLiteral("New Playlist"),
                                                       QStringLiteral("Playlist Name"),
                                                       QLineEdit::Normal,
                                                       QStringLiteral(""), &ok);

    if (!ok)
        return;

    if (playlistName.isEmpty()) {
        QMessageBox msg;
        msg.setText(QStringLiteral("No playlist name was entered"));
        msg.exec();
        return;
    }

    m_newPlaylist = playlistName;
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
