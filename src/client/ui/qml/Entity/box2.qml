import QtQuick 2.12

Item {
    id: root

    width: parent.width
    height: parent.height

    ListView {
        anchors.fill: parent
        anchors.margins: 20

        clip: true

        model: 10

        delegate: numberDelegate
        spacing: 2
    }

    Component {
        id: numberDelegate

        Rectangle {
            id: root
            width: parent.width
            height: 40
            color: "#ffffff"
            border.color: Qt.darker(color, 1.2)
            property alias text: label.text
            property color fontColor: '#1f1f1f'
            Text {
                id: label
                anchors.centerIn: parent
                font.pixelSize: 14
                color: root.fontColor
            }
        }
    }
}
