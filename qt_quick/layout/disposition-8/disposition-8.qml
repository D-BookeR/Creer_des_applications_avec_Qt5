import QtQuick 2.0

Rectangle {
    width: grid.width + 20
    height: grid.height + 20
    Grid {
        id: grid
        x: 10; y: 10
        rows: 3; columns: 3
        spacing: 10
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "0"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "1"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "2"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "3"
            }
        }
        Item {
            width: 30; height: 30
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "4"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "5"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "6"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "7"
            }
        }
    }
}

