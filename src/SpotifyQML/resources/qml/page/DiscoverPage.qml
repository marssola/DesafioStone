import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import SpotQt 1.0

Page {
    id: pagePlaylists

    property var searchedTracks: Array()

    padding: 0
    topPadding: 20
    bottomPadding: 20

    header: ToolBar {
        id: toolBar

        background: Item {}

        RowLayout {
            anchors.fill: parent
            anchors.margins: 10
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            spacing: 10

            TextField {
                id: searchField

                Layout.fillWidth: true
                placeholderText: qsTr("Type to search")
            }

            ToolButton {
                enabled: searchField.text.length > 0

                highlighted: true
                flat: true
                icon.name: "search"

                onClicked: pagePlaylists.searchedTracks = spotify.searchMusic(searchField.text)
            }
        }
    }

    Label {
        id: labelNoTrack

        visible: pagePlaylists.searchedTracks.length === 0
        text: qsTr("Nothing")

        anchors.centerIn: parent
    }

    ListView {
        id: listSearchedTracks
        visible: pagePlaylists.searchedTracks.length > 0

        anchors.fill: parent
        spacing: 5
        clip: true

        model: pagePlaylists.searchedTracks
        delegate: ItemDelegate {
            width: listSearchedTracks.width
            height: 60

            highlighted: listSearchedTracks.currentIndex === index

            contentItem: RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 10
                anchors.rightMargin: 10

                Item{
                    Layout.preferredWidth: 100
                    Layout.fillHeight: true

                    Image {
                        id: imageAlbum
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit

                        source: modelData.image
                    }

                    BusyIndicator {
                        visible: imageAlbum.status === Image.Loading
                        anchors.centerIn: parent
                        anchors.fill: parent
                    }
                }

                Label {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    text: modelData.name

                    elide: Label.ElideRight
                    wrapMode: Label.WordWrap
                    verticalAlignment: Label.AlignVCenter
                }
            }

            onClicked: {
                listSearchedTracks.currentIndex = index
                dialogAddToPlaylist.open()
            }
        }        
    }

    Dialog {
        id: dialogAddToPlaylist

        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        closePolicy: Dialog.NoAutoClose

        width: 350
        height: 250
        anchors.centerIn: parent

        title: qsTr("Add to playlist")

        ComboBox {
            id: comboPlaylists

            width: parent.width
            anchors.centerIn: parent

            editable: true
            model: playlists.playlistsName
            onModelChanged: currentIndex = -1
        }

        onAccepted: {
            if (comboPlaylists.currentIndex < 0 && comboPlaylists.editText.length === 0) {
                listSearchedTracks.currentIndex = -1
                dialogAddToPlaylist.visible = true
                return
            }

            const searchedTrack = pagePlaylists.searchedTracks[listSearchedTracks.currentIndex]
            searchedTrack["playlistName"] = (comboPlaylists.currentIndex < 0 && comboPlaylists.editText.length > 0) ? comboPlaylists.editText :
                                                                                                                      comboPlaylists.currentText
            playlists.addPlaylist(playlists.createTrack(searchedTrack))

            clear()
        }

        onRejected: clear()

        function clear() {
            comboPlaylists.editText = ""
            comboPlaylists.currentIndex = -1
            listSearchedTracks.currentIndex = -1
        }
    }
}
