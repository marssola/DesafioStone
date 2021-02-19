import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    id: page

    property string playlistsName
    property var playlist: Array()

    onPlaylistsNameChanged: {
        pagePlaylists.header.title = page.playlistsName
        page.playlist = getPlaylist(page.playlistsName)
    }

    ListView {
        id: listSearchedTracks

        anchors.fill: parent
        spacing: 5
        clip: true

        model: page.playlist
        delegate: SwipeDelegate {
            id: item
            width: listSearchedTracks.width
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

                onAccepted: {
                    console.log("Remover esta melda")
                }

                onClosed: item.swipe.close()
            }

            onClicked: item.swipe.close()
        }
    }
}
