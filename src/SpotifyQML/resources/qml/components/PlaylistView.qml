import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    id: page

    property string playlistsName
    property var playlist: Array()

    onPlaylistsNameChanged: {
        pagePlaylists.header.title = page.playlistsName
        page.playlist = playlists.getPlaylistByName(page.playlistsName)
    }

    ListView {
        id: tracks

        anchors.fill: parent
        spacing: 5
        clip: true

        model: page.playlist
        delegate: SwipeDelegate {
            id: item
            width: tracks.width
            height: 60

            contentItem: RowLayout {
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

                    text: modelData.track

                    elide: Label.ElideRight
                    wrapMode: Label.WordWrap
                    verticalAlignment: Label.AlignVCenter
                }
            }

            swipe.right: Label {
                id: deleteLabel

                text: qsTr("Remove")
                verticalAlignment: Label.AlignVCenter
                padding: 12
                height: parent.height
                anchors.right: parent.right

                SwipeDelegate.onClicked: dialogConfirmDeleteTrack.open()

                background: Rectangle {
                    color: Qt.darker("tomato", deleteLabel.SwipeDelegate.pressed ? 1.8 : 1.2)
                }
            }

            Dialog {
                id: dialogConfirmDeleteTrack

                width: 300
                modal: true

                anchors.centerIn: parent
                standardButtons: Dialog.Yes | Dialog.No
                title: qsTr("Warning")

                Label {
                    anchors.centerIn: parent
                    text: qsTr("Do you really want to remove this track")
                }

                onAccepted: playlists.removeTrack(index, page.playlistsName)

                onClosed: item.swipe.close()
            }

            onClicked: item.swipe.close()
        }
    }

    Button {
        text: qsTr("Play")
        icon.name: "play-circle-filled-white"

        highlighted: true
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 30
        anchors.bottomMargin: 30

        onClicked: {
            mediaPlayer.stop()
            mediaPlayer.playlist.currentIndex = -1
            mediaPlayer.queue = page.playlist
            mediaPlayer.playlist.clear()

            for (let k in page.playlist)
                mediaPlayer.playlist.addItem(page.playlist[k].previewUrl)

            mediaPlayer.play()
        }
    }

    Connections {
        target: playlists

        function onPlaylistsChanged() {
            page.playlist = playlists.getPlaylistByName(page.playlistsName)
        }
    }
}
