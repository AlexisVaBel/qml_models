import QtQuick 2.12

import "../Components"

Item {

    id: root

    width: parent.width
    height: parent.height
    Column {
        width: parent.width
        height: parent.height
        anchors.margins: 20

        Row {

            NormalButton {
                id: buttonHide
                caption: "Hide"

                MouseArea {
                    anchors.fill: parent
                    onClicked: listView.stateVisible = !listView.stateVisible
                }
            }

            NormalButton {
                id: buttonSwap
                caption: "Swap"

                MouseArea {
                    anchors.fill: parent
                    onClicked: listView.height = listView.height
                               > 0 ? listView.height = 0 : listView.height = root.height
                }
            }
        }

        ListView {
            id: listView
            property bool stateVisible: true

            width: parent.width
            height: parent.height - buttonHide.height

            clip: true

            model: 6

            delegate: numberDelegate
            spacing: 2

            header: headerComponent
            footer: footerComponent

            highlight: Rectangle {
                color: "lightsteelblue"
                radius: 5
            }

            states: [
                State {
                    when: listView.stateVisible
                    PropertyChanges {
                        target: listView
                        opacity: 1.0
                    }
                },
                State {
                    when: !listView.stateVisible
                    PropertyChanges {
                        target: listView
                        opacity: 0.0
                    }
                }
            ]
            transitions: [
                Transition {
                    NumberAnimation {
                        property: "opacity"
                        duration: 300
                    }
                },
                Transition {
                    NumberAnimation {
                        property: "height"
                        duration: 1500
                        easing.type: Easing.InOutQuad
                    }
                }
            ]
        }
    }

    Component {
        id: headerComponent

        Rectangle {
            color: "silver"
            border.color: "silver"
            width: parent.width
            height: 20
        }
    }

    Component {
        id: footerComponent

        Rectangle {
            color: "silver"
            border.color: "silver"
            width: parent.width
            height: 20
        }
    }

    Component {
        id: numberDelegate

        Rectangle {
            color: "gainsboro"
            border.color: "silver"
            width: parent.width
            height: 40
        }
    }
}
