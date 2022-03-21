import QtQuick 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML-C++ nodes")

    Pane {
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent
            TabBar {
                id: tabBar
                Layout.preferredWidth: 450
                Layout.fillHeight: false
                TabButton {
                    id: tabFirst
                    text: qsTr("First")
                }
                TabButton {
                    id: tabSecond
                    text: qsTr("Second")
                }
                TabButton {
                    id: tabThird
                    text: qsTr("Third")
                }
                TabButton {
                    id: tabFourth
                    text: qsTr("Fourth")
                }
            }

            StackLayout {
                clip: true
                Layout.fillWidth: true
                Layout.fillHeight: true
                currentIndex: tabBar.currentIndex
                Item {
                    Loader {
                        anchors.fill: parent
                        source: "qrc:/ui/qml/Entity/box1.qml"
                    }
                }
                Item {
                    Loader {
                        anchors.fill: parent
                        source: "qrc:/ui/qml/Entity/box2.qml"
                    }
                }
                Item {
                    Loader {
                        anchors.fill: parent
                        source: "qrc:/ui/qml/Entity/box3.qml"
                    }
                }
                Item {
                    Loader {
                        anchors.fill: parent
                        source: "qrc:/ui/qml/Entity/box4.qml"
                    }
                }
            }
        }
    }
}
