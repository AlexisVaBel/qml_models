import QtQuick 2.12

import "../Components"

Rectangle {
    id: root

    color: "white"
    border.width: 1
    radius: 5
    width: parent.width
    height: parent.height

    Column {
        id: blueSource

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 5
        width: 64
        spacing: -16

        Repeater {
            model: 81
            delegate: DragTile {
                colorKey: "blue"
            }
        }
    }

    Grid {
        anchors.left: blueSource.right
        anchors.top: root.top
        width: parent.width - blueSource.width
        anchors.bottom: root.bottom
        anchors.margins: 5

        opacity: 0.5

        Repeater {
            model: 256
            delegate: DropTile {
                colorKey: "blue"
            }
        }
    }
}
