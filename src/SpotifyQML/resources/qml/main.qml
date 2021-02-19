import QtQuick 2.12
import QtQuick.Controls 2.12

import "./page"

ApplicationWindow {
    width: 480
    height: 640
    visible: true
    title: qsTr("Spotify QML")

    MainPage {
        id: mainPage

        anchors.fill: parent
    }
}
