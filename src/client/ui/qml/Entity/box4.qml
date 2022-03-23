import QtQuick 2.12

import QuickNodes 2.0 as QNo

//import "qrc:/QuickNodes" as QNo
QNo.Navigable {
    id: root
    clip: true
    anchors.fill: parent

    Text {
        id: valueText
        text: "4"
        anchors.centerIn: root.Center

        font.bold: true
        font.pointSize: root.height * 0.33
    }
}
