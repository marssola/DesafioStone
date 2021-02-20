import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../components"

Page {
    id: pagePlaylists

    Label {
        visible: mediaPlayer.queue.length === 0

        text: qsTr("Nothing")
        anchors.centerIn: parent
    }

    ListView {
        id: tracks

        anchors.fill: parent
        spacing: 5
        clip: true

        model: mediaPlayer.queue
        delegate: SwipeDelegate {
            id: item
            width: tracks.width
            height: 60

            highlighted: mediaPlayer.currentIndex === index

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
        }
    }
}
