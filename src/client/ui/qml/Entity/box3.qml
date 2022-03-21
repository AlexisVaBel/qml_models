import QtQuick 2.12

import "../Components"

Rectangle {
    id: root

    color: "white"
    border.width: 1
    radius: 5
    width: parent.width
    height: parent.height

    Grid {
        anchors.left: blueSource.right
        anchors.top: root.top
        anchors.right: root.right
        anchors.bottom: root.bottom
        anchors.margins: 5

        opacity: 0.5

        columns: 126
        rows: 126

        Repeater {
            model: 81
            delegate: DropTile {
                colorKey: "blue"
            }
        }
    }

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
}
