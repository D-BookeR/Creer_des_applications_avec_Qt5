import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    width: grid.width + 20
    height: grid.height + 20
    GridLayout {
        id: grid
        x: 10; y: 10
        rows: 3; columns: 3
        columnSpacing: 10
        rowSpacing: 10
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Layout.row: 0
            Layout.column: 0
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "0"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Layout.row: 0
            Layout.column: 1
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "1"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Layout.row: 0
            Layout.column: 2
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "2"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Layout.row: 1
            Layout.column: 0
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "3"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Layout.row: 1
            Layout.column: 2
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "4"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Layout.row: 2
            Layout.column: 0
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "5"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Layout.row: 2
            Layout.column: 1
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "6"
            }
        }
        Rectangle {
            color: "lightgreen"
            width: 30; height: 30
            Layout.row: 2
            Layout.column: 2
            Text {
                anchors.centerIn: parent
                font.pixelSize: 14
                text: "7"
            }
        }
    }
}

