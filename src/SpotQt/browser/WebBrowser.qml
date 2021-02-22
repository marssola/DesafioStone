import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtWebEngine 1.10

ApplicationWindow {
    id: window

    width: 1024
    height: 768

    visible: true
    flags: Qt.Dialog | Qt.WindowTitleHint | Qt.CustomizeWindowHint

    title: qsTr("Spotify Login")

    WebEngineView {
        id: webView

        z: 1
        anchors.fill: parent
    }

    Button {
        z: 10
        visible: webView.canGoBack

        text: qsTr("Back")

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10

        highlighted: true

        onClicked: webView.goBack()
    }

    function loadUrl(url) {
        webView.url = url
    }

    onClosing: {
        close.accepted = false
    }

    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }
}
