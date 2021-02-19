import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    id: page

    footer: TabBar {
        id: bottomNavigation

        width: parent.width
        currentIndex: 0

        TabButton {
            text: qsTr("Playlists")
        }

        TabButton {
            text: qsTr("Discover")
        }

        TabButton {
            text: qsTr("Queue")
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
