import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Rectangle {
    id: control

    width: parent.width
    height: 60

    color: "#99000000"

    Row {
        anchors.centerIn: parent
        spacing: 10

        ToolButton {
            id: buttonPlayPause
            icon.name: mediaPlayer.playing ? "pause" : "play-arrow"
            onClicked: mediaPlayer.playing ? mediaPlayer.pause() : mediaPlayer.play()
        }

        ToolButton {
            icon.name: "stop"
            onClicked: mediaPlayer.stop()
        }

        ToolButton {
            icon.name: "skip-previous"
            onClicked: mediaPlayer.playlist.previous()
        }

        ToolButton {
            icon.name: "skip-next"
            onClicked: mediaPlayer.playlist.next()
        }

        Label {
            width: control.width - ((buttonPlayPause.width + parent.spacing) * 4)
            height: parent.height

            text: mediaPlayer.trackPlaying

            elide: Label.ElideRight
            wrapMode: Label.WrapAnywhere
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter

            ProgressBar {
                width: parent.width
                anchors.bottom: parent.bottom

                from: 0
                to: mediaPlayer.duration
                value: mediaPlayer.position
            }
        }
    }
}
