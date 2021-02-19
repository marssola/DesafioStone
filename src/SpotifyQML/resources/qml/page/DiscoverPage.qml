import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

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
                highlighted: true
                flat: true
                icon.name: "search"

                onClicked: {
                    pagePlaylists.searchedTracks = [
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d000048519683e5d7361bb80bfb00f46d",
                                    "name": "Paranoid",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/c3c74a5d2214f66307037df432d0ba2480e708fe?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d000048519683e5d7361bb80bfb00f46d",
                                    "name": "Iron Man",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/b5afd236ad1f6a6df6ba6994c665f648c4d0fda4?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d000048511311a92b0ca83a5154c5a5e7",
                                    "name": "Black Sabbath",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/4bf1e398de0edc42cd4a3efb4be5fa33f1aa0ac3?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d000048519683e5d7361bb80bfb00f46d",
                                    "name": "War Pigs",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/7b0420fab47dfbf060312207b3f67d8bea8f04ba?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d00004851b7ec2b4b9c76b3b737990a42",
                                    "name": "Children of the Grave",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/393b35840a1a96f08080adb8d6942e9f5c5feeff?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d000048511311a92b0ca83a5154c5a5e7",
                                    "name": "N.I.B.",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/82ab9db4cbf7987f7bb3dd912d3e4f7b4f020961?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d00004851876dd2bbe17e15208b25779b",
                                    "name": "Sabbath Bloody Sabbath",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/e1dc687b01104a628b7b5e09cacbdd784e8e4a92?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d000048511714d5e8b43f9e63572d550d",
                                    "name": "Heaven and Hell - 2009 Remaster",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/160db635490b1411f8630aa22c03eb724687e986?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d00004851d198e0a1a43c010afb480b3b",
                                    "name": "Changes",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/cefad0f88845e75d7347fa8d83b0118058053b90?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d000048519683e5d7361bb80bfb00f46d",
                                    "name": "Planet Caravan",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/283911383091073421dc63efd0a6ec13d00980c0?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d000048511311a92b0ca83a5154c5a5e7",
                                    "name": "The Wizard",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/9690fdff672dba332aeeee1c207b8bac52ac2424?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Coven",
                                    "image": "https://i.scdn.co/image/ab67616d00004851f2805ab3df685f507b44afbd",
                                    "name": "Black Sabbath",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/b68be9fae9e10914ffff3db64518d38802600629?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d00004851b7ec2b4b9c76b3b737990a42",
                                    "name": "Sweet Leaf",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/e634b75b7ad3ac951c3f196c8027e4e7e7f9fc07?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Type O Negative",
                                    "image": "https://i.scdn.co/image/ab67616d00004851a0bd2873503245430e61683d",
                                    "name": "Black Sabbath",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/6c7f372be13c17109e11c20619131b4db532441c?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d00004851b7ec2b4b9c76b3b737990a42",
                                    "name": "Into the Void",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/0710f9eff1e0936c3bf8eba0e1489a7465da84cc?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d000048511d21d6c1740f63ed5c9519c8",
                                    "name": "Black Sabbath - Live; 2009 Remaster",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/6d8c5c21ba3549bf9a332ed68f508a91ad49d14c?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Black Sabbath",
                                    "image": "https://i.scdn.co/image/ab67616d00004851b7ec2b4b9c76b3b737990a42",
                                    "name": "Solitude",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/7d9ddffb1c2a329d891b39a7ec28d28e5ec3bce8?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                },
                                {
                                    "artist": "Adrenaline Mob",
                                    "image": "https://i.scdn.co/image/ab67616d000048513aefc6b0d3940d05f772aa03",
                                    "name": "Black Sabbath Medley",
                                    "previewUrl": "https://p.scdn.co/mp3-preview/5fc875e3165615c38d77fbe21289ccd18910eef9?cid=f8023ea988e548df83fb42b5ce1e1a20"
                                }
                            ]
                }
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

            currentIndex: -1
            editable: true
        }

        onAccepted: {
            if (comboPlaylists.currentIndex < 0 && comboPlaylists.editText.length === 0) {
                listSearchedTracks.currentIndex = -1
                dialogAddToPlaylist.visible = true
                return
            }

            if (comboPlaylists.currentIndex < 0 && comboPlaylists.editText.length > 0) {
                console.log(comboPlaylists.editText, JSON.stringify(pagePlaylists.searchedTracks[listSearchedTracks.currentIndex], null, 4))
                listSearchedTracks.currentIndex = -1
                return
            }

            listSearchedTracks.currentIndex = -1
            console.log(comboPlaylists.currentIndex, comboPlaylists.currentText, comboPlaylists.currentValue)
        }

        onRejected: {
            comboPlaylists.editText = ""
            comboPlaylists.currentIndex = -1
            listSearchedTracks.currentIndex = -1
        }
    }
}
