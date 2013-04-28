import QtQuick 2.0

Rectangle {
    width: 525; height: 385
    Column {
        x: 25; y: 25
        spacing: 25
        Text {
            font.pointSize: 16
            height: 30
            text: "layoutDirection: Qt.LeftToRight"
        }
        Row {
            spacing: 25
            layoutDirection: Qt.LeftToRight
            Rectangle {
                width: 100; height: 100
                color: "lightgreen"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
                    text: "1"
                }
            }
            Rectangle {
                width: 100; height: 100
                color: "lightgreen"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
                    text: "2"
                }
            }
            Rectangle {
                width: 100; height: 100
                color: "lightgreen"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
                    text: "3"
                }
            }
            Rectangle {
                width: 100; height: 100
                color: "lightgreen"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
                    text: "4"
                }
            }
        }

        Text {
            font.pointSize: 16
            height: 30
            text: "layoutDirection: Qt.RightToLeft"
        }
        Row {
            spacing: 25
            layoutDirection: Qt.RightToLeft
            Rectangle {
                width: 100; height: 100
                color: "lightblue"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
                    text: "1"
                }
            }
            Rectangle {
                width: 100; height: 100
                color: "lightblue"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
                    text: "2"
                }
            }
            Rectangle {
                width: 100; height: 100
                color: "lightblue"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
                    text: "3"
                }
            }
            Rectangle {
                width: 100; height: 100
                color: "lightblue"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
                    text: "4"
                }
            }
        }
    }
}

