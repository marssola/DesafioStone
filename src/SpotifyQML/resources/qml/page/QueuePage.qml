import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../components"

Page {
    id: pagePlaylists

    property var queue: [
        {
            "artist": "Black Sabbath",
            "image": "https://i.scdn.co/image/ab67616d000048519683e5d7361bb80bfb00f46d",
            "playlistName": "Metal",
            "previewUrl": "https://p.scdn.co/mp3-preview/b5afd236ad1f6a6df6ba6994c665f648c4d0fda4?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Iron Man"
        },
        {
            "artist": "Black Sabbath",
            "image": "https://i.scdn.co/image/ab67616d000048516e251a69eecae8feb5744ea4",
            "playlistName": "Metal",
            "previewUrl": "https://p.scdn.co/mp3-preview/73bf1273fd0ee6f95a19dd4de4e6e8adb4415853?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Children of the Sea - 2009 Remaster"
        },
        {
            "artist": "Black Sabbath",
            "image": "https://i.scdn.co/image/ab67616d00004851b7ec2b4b9c76b3b737990a42",
            "playlistName": "Metal",
            "previewUrl": "https://p.scdn.co/mp3-preview/393b35840a1a96f08080adb8d6942e9f5c5feeff?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Children of the Grave"
        },
        {
            "artist": "Accept",
            "image": "https://i.scdn.co/image/ab67616d0000485139bcae6f92f8ba8941dc2fb1",
            "playlistName": "Metal",
            "previewUrl": "https://p.scdn.co/mp3-preview/a6f825cf4e8ba18c93c8347b1c3131492cb55a18?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Blood of the Nations"
        },
        {
            "artist": "Accept",
            "image": "https://i.scdn.co/image/ab67616d0000485139bcae6f92f8ba8941dc2fb1",
            "playlistName": "Metal",
            "previewUrl": "https://p.scdn.co/mp3-preview/1756c3e6e7a8d121a272bfb8b44ecf939fab6f54?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Beat the Bastards"
        },
        {
            "artist": "Accept",
            "image": "https://i.scdn.co/image/ab67616d0000485139bcae6f92f8ba8941dc2fb1",
            "playlistName": "Metal",
            "previewUrl": "https://p.scdn.co/mp3-preview/0f9d8f54a3038e7be3c4e4f89abf55893a82e40e?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Time Machine"
        }
    ]

    Label {
        visible: pagePlaylists.queue.length === 0

        text: qsTr("Nothing")
        anchors.centerIn: parent
    }

    ListView {
        id: listSearchedTracks

        anchors.fill: parent
        spacing: 5
        clip: true

        model: pagePlaylists.queue
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
