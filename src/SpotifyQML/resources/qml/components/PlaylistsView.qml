import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Page {
    id: page

    Label {
        visible: playlists.playlistsName.length === 0

        text: qsTr("Nothing")
        anchors.centerIn: parent
    }

    Flickable {
        visible: playlists.playlistsName.length > 0

        anchors.fill: parent
        contentHeight: flowPlaylist.implicitHeight

        Flow {
            id: flowPlaylist
            anchors.fill: parent
            spacing: 20

            property int widthItem: 200

            topPadding: 20
            bottomPadding: 20
            leftPadding: (pagePlaylists.width % flowPlaylist.widthItem - flowPlaylist.spacing) / 2
            rightPadding: rightPadding

            Repeater {
                model: playlists.playlistsName

                delegate: ItemDelegate {
                    id: delegate
                    width: flowPlaylist.widthItem
                    height: width

                    onClicked: stack.push("PlaylistView.qml", { playlistsName: modelData })

                    contentItem: Label {
                        anchors.fill: parent

                        text: modelData
                        font.pixelSize: 18
                        font.bold: true
                        font.capitalization: Font.AllUppercase

                        elide: Label.ElideRight
                        wrapMode: Label.WrapAnywhere
                        horizontalAlignment: Label.AlignHCenter
                        verticalAlignment: Label.AlignVCenter
                    }

                    background: Rectangle {
                        id: background

                        color: "#222"
                        radius: 10

                        Grid {
                            anchors.centerIn: parent
                            columns: 2
                            opacity: 0.40

                            Repeater {
                                id: repeaterImages

                                model: playlists.imagesFromPlaylist(modelData)
                                property int totalImages: model.length

                                Image {
                                    id: imageAlbum

                                    width: 100
                                    height: width

                                    fillMode: Image.PreserveAspectCrop
                                    source: repeaterImages.model[index]
                                }
                            }
                        }

                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: Rectangle {
                                width: background.width
                                height: background.height
                                radius: background.radius
                            }
                        }

                        Ripple {
                            anchors.fill: parent

                            clipRadius: background.radius
                            anchor: background

                            active: delegate.pressed
                            pressed: delegate.pressed

                            color: "#3f000000"
                        }
                    }
                }
            }
        }
    }
}
