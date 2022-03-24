import QtQuick 2.0

Rectangle {
    id: root
    color: "black"
    border.color: "silver"
    width: 128
    height: 32
    property alias caption: name.text
    Text {
        anchors.centerIn: root.Center

        id: name
        text: caption
        color: "white"
    }
}
