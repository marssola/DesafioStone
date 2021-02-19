import QtQuick 2.12
import QtQuick.Controls 2.12

import "../components"

Page {
    id: pagePlaylists

    Label {
        text: qsTr("Nothing")
        anchors.centerIn: parent
    }

    QueuePlayer {
        id: queuePlayer
    }
}
