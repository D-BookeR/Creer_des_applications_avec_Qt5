import QtQuick 2.0

Column {
    x: 5; y: 5
    width: 280; height: 145
    spacing: 5

    Text {
        font.pointSize: 14
        height: 30
        text: "layoutDirection: Qt.LeftToRight"
    }
    Row {
        spacing: 5
        layoutDirection: Qt.LeftToRight
        Repeater {
            model: 5
            Rectangle {
                width: 50; height: 30
                color: "lightgreen"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 14
                    text: index
                }
            }
        }
    }

    Text {
        font.pointSize: 14
        height: 30
        text: "layoutDirection: Qt.RightToLeft"
    }
    Row {
        spacing: 5
        layoutDirection: Qt.RightToLeft
        Repeater {
            model: 5
            Rectangle {
                width: 50; height: 30
                color: "lightblue"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 14
                    text: index
                }
            }
        }
    }
}
