import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../components"
import SpotQt 1.0

Page {
    id: page

    footer: Column {
        width: parent.width
        height: queuePlayer.height +  bottomNavigation.height

        QueuePlayer {
            id: queuePlayer
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

    StackLayout {
        id: stackLayout
        currentIndex: bottomNavigation.currentIndex

        anchors.fill: parent

        PlaylistsPage {}

        DiscoverPage {}

        QueuePage {}
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
}
