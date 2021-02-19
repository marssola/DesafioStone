import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Page {
    id: pagePlaylists

    property var playlistsName: ["Metal", "Prog", "Sabbath"]
    property var tracks: [
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
        },
        {
            "artist": "Rush",
            "image": "https://i.scdn.co/image/ab67616d000048515b322357457e9e5b5e2cc1de",
            "playlistName": "Prog",
            "previewUrl": "https://p.scdn.co/mp3-preview/8ce77092a59323984db75fb2497317e883cf15d2?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Xanadu - Remastered"
        },
        {
            "artist": "Pink Floyd",
            "image": "https://i.scdn.co/image/ab67616d00004851f05e5ac32fdd79d100315a20",
            "playlistName": "Prog",
            "previewUrl": "https://p.scdn.co/mp3-preview/83c1f92586bfa2a326b3c7c69aeb9321007f5055?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Time"
        },
        {
            "artist": "Pink Floyd",
            "image": "https://i.scdn.co/image/ab67616d00004851d8fa5ac6259dba33127b398a",
            "playlistName": "Prog",
            "previewUrl": "https://p.scdn.co/mp3-preview/7ce0d4e5f0ffcf8fe1a312c9c2f9331c8d2bf994?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Wish You Were Here"
        },
        {
            "artist": "Pink Floyd",
            "image": "https://i.scdn.co/image/ab67616d000048510671b43480c4cfb4b5667857",
            "playlistName": "Prog",
            "previewUrl": "https://p.scdn.co/mp3-preview/4817674d515fac5c9cdecacc459a17c49a1bf9ff?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Dogs"
        },
        {
            "artist": "Pink Floyd",
            "image": "https://i.scdn.co/image/ab67616d00004851288d32d88a616b9a278ddc07",
            "playlistName": "Prog",
            "previewUrl": "https://p.scdn.co/mp3-preview/daf1a7a5cf0ca8fc212ce61ac3d058fb12e2814f?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Comfortably Numb"
        },
        {
            "artist": "Black Sabbath",
            "image": "https://i.scdn.co/image/ab67616d00004851b7ec2b4b9c76b3b737990a42",
            "playlistName": "Sabbath",
            "previewUrl": "https://p.scdn.co/mp3-preview/393b35840a1a96f08080adb8d6942e9f5c5feeff?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Children of the Grave"
        },
        {
            "artist": "Black Sabbath",
            "image": "https://i.scdn.co/image/ab67616d000048514f7e152e7581f7c87327c8c5",
            "playlistName": "Sabbath",
            "previewUrl": "https://p.scdn.co/mp3-preview/679d9033ac0b51555978a6f7890166e0d420f6ca?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Sabbath Bloody Sabbath - Live"
        },
        {
            "artist": "Black Sabbath",
            "image": "https://i.scdn.co/image/ab67616d00004851b7ec2b4b9c76b3b737990a42",
            "playlistName": "Sabbath",
            "previewUrl": "https://p.scdn.co/mp3-preview/0710f9eff1e0936c3bf8eba0e1489a7465da84cc?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Into the Void"
        },
        {
            "artist": "Bruce Dickinson",
            "image": "https://i.scdn.co/image/ab67616d00004851a0bd2873503245430e61683d",
            "playlistName": "Sabbath",
            "previewUrl": "https://p.scdn.co/mp3-preview/1b2378b1aef92f789373613641d55b8780982c8f?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "Sabbath Bloody Sabbath"
        },
        {
            "artist": "Black Sabbath",
            "image": "https://i.scdn.co/image/ab67616d000048511311a92b0ca83a5154c5a5e7",
            "playlistName": "Sabbath",
            "previewUrl": "https://p.scdn.co/mp3-preview/82ab9db4cbf7987f7bb3dd912d3e4f7b4f020961?cid=f8023ea988e548df83fb42b5ce1e1a20",
            "track": "N.I.B."
        }
    ]

    header: ToolBar {
        visible: stack.depth > 1
        property string title

        RowLayout {
            anchors.fill: parent

            ToolButton {
                text: "<"

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
                text: "Remove"

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
            console.log("Remover esta melda")
        }
    }

    function extracImagesFromPlaylist(playlistsName) {
        return pagePlaylists.tracks.filter(function (item) {
            return item.playlistName === playlistsName
        }).map(function(item) {
            return item.image
        }).filter(function (item, pos, self) {
            return self.indexOf(item) === pos
        }).slice(0, 4)
    }

    function getPlaylist(playlistsName) {
        return pagePlaylists.tracks.filter(function (item) {
            return item.playlistName === playlistsName
        });
    }
}
