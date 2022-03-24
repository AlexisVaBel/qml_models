import QtQuick 2.12
import QtQuick.Controls 2.12

import QuickNodes 2.0 as QNo

QNo.Navigable {
    id: navigable
    clip: true
    anchors.fill: parent

    Slider {
        anchors.top: navigable.top
        anchors.horizontalCenter: navigable.horizontalCenter
        width: navigable.width / 2
        //        maximumValue: navigable.zoomMax > 0. ? navigable.zoomMax : 10.
        //        minimumValue: navigable.zoomMin
        stepSize: 0.0 // Non 0 stepSize will create binding loops until you protect the onValueChanged with a fuzzyCompare against zoom+-stepSize
        value: navigable.zoom
        onValueChanged: {
            navigable.zoom = value
        }
    }
    Rectangle {
        anchors.fill: navigable
        border.color: "black"
        Text {
            id: valueText
            text: "4"
            anchors.centerIn: navigable.Center

            font.bold: true
        }
        QNo.PieChart {
            id: aPieChart
            anchors.centerIn: parent
            width: 100
            height: 100
            name: "A simple pie chart"
            color: "red"
        }
    }
}
