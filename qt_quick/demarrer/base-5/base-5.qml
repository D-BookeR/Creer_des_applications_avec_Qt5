import QtQuick 2.0

Row {
    width: 450; height: 100
    Rectangle {
        width: 150; height: 100
        color: "#550000FF"
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            text: "Bleu"
        }
    }
    Rectangle {
        width: 150; height: 100
        color: Qt.tint("#550000FF", "#55FF0000")
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            text: "Tint"
        }
    }
    Rectangle {
        width: 150; height: 100
        color: "#55FF0000"
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            text: "Rouge"
        }
    }
}
