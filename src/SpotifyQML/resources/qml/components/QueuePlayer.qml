import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Rectangle {
    id: control

    anchors.bottom: parent.bottom
    width: parent.width
    height: 60

    color: Qt.rgba(Material.accentColor.r, Material.accentColor.g, Material.accentColor.b, 0.3)

    Row {
        anchors.centerIn: parent
        spacing: 10

        ToolButton {
            id: buttonPlayPause
            icon.name: "play-arrow"
        }

        ToolButton {
            icon.name: "stop"
        }

        ToolButton {
            icon.name: "skip-previous"
        }

        ToolButton {
            icon.name: "skip-next"
        }

        Label {
            width: control.width - ((buttonPlayPause.width + parent.spacing) * 4)
            height: parent.height

            text: "Artist - Music"

            elide: Label.ElideRight
            wrapMode: Label.WrapAnywhere
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter
        }
    }
}
