import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtMultimedia 5.15

import "../components"
import SpotQt 1.0

Page {
    id: page

    footer: Column {
        width: parent.width
        height: bottomNavigation.height + (queuePlayer.visible ? queuePlayer.height : 0)

        QueuePlayer {
            id: queuePlayer

            visible: mediaPlayer.currentIndex > -1
        }

        TabBar {
            id: bottomNavigation

            width: parent.width
            currentIndex: 1

            TabButton {
                text: qsTr("Playlists")
                icon.name: "playlist-play"
            }

            TabButton {
                text: qsTr("Discover")
                icon.name: "search"
            }

            TabButton {
                text: qsTr("Queue")
                icon.name: "queue-music"
            }
        }
    }

    Spotify {
        id: spotify
    }

    Playlists {
        id: playlists

        property var playlistsName: Array()

        onPlaylistsChanged: playlists.playlistsName = playlists.getPlaylistsName()
        Component.onCompleted: playlists.loadAll(playlists)
    }

    MediaPlayer {
        id: mediaPlayer

        property bool playing: false
        property var queue: Array()
        property int currentIndex: playlist.currentIndex
        property string trackPlaying: mediaPlayer.currentIndex < 0 ? "" : queue[currentIndex].artist + " - " + queue[currentIndex].track

        onPlaying: mediaPlayer.playing = true
        onPaused: mediaPlayer.playing = false
        onStopped: {
            mediaPlayer.playing = false
            if (mediaPlayer.playlist.currentIndex === -1) {
                mediaPlayer.queue = []
                mediaPlayer.playlist.clear()
            }
        }

        playlist: Playlist {}
    }

    StackLayout {
        id: stackLayout
        currentIndex: bottomNavigation.currentIndex

        anchors.fill: parent

        PlaylistsPage {}

        DiscoverPage {}

        QueuePage {}
    }
}
