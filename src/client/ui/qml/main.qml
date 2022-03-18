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
    }
    ColumnLayout {
        anchors.fill: parent
        TabBar {
            id: tabBar
            Layout.preferredWidth: 450
            Layout.fillHeight: false
            TabButton {
                text: qsTr("First")
            }
            TabButton {
                text: qsTr("Second")
            }
            TabButton {
                text: qsTr("Third")
            }
            TabButton {
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
                    source: "qrc:/ui/qml/entity/box.qml"
                }
            }
            Item {
                Loader {
                    anchors.fill: parent
                    source: "qrc:/ui/qml/entity/box2.qml"
                }
            }
            Item {
                Loader {
                    anchors.fill: parent
                    source: "qrc:/ui/qml/entity/box3.qml"
                }
            }
            Item {
                Loader {
                    anchors.fill: parent
                    source: "qrc:/ui/qml/entity/box4.qml"
                }
            }
        }
    }
}
