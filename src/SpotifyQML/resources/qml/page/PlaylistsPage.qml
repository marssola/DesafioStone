import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import "../components"

Page {
    id: pagePlaylists

    header: ToolBar {
        visible: stack.depth > 1
        property string title

        RowLayout {
            anchors.fill: parent

            ToolButton {
                icon.name: "arrow-back"
                onClicked: stack.pop()
            }

            Label {
                text: pagePlaylists.header.title
                Layout.fillWidth: true
                Layout.fillHeight: true

                font.bold: true
                font.pixelSize: 18
                font.capitalization: Font.AllUppercase

                elide: Label.ElideRight
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
            }

            ToolButton {
                icon.name: "delete"
                onClicked: dialogConfirmDeletePlaylist.open()
            }
        }

        background: Item {}
    }

    StackView {
        id: stack

        anchors.fill: parent
        initialItem: PlaylistsView {}
    }

    Dialog {
        id: dialogConfirmDeletePlaylist

        width: 300
        anchors.centerIn: parent
        standardButtons: Dialog.Yes | Dialog.No

        modal: true
        title: qsTr("Warning")

        Label {
            anchors.centerIn: parent
            text: qsTr("Do you really want to remove this playlist")
        }

        onAccepted: {
            stack.pop()
            playlists.removePlaylist(pagePlaylists.header.title)
        }
    }
}
