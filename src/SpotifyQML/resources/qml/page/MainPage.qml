import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    id: page

    footer: TabBar {
        id: bottomNavigation

        width: parent.width
        currentIndex: 2

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

    StackLayout {
        id: stackLayout
        currentIndex: bottomNavigation.currentIndex

        anchors.fill: parent

        PlaylistsPage {}

        DiscoverPage {}

        QueuePage {}
    }
}
