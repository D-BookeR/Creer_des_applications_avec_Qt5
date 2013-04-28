import QtQuick 2.0

Row {
    Rectangle {
        width: 150; height: 150
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            text: "Interligne\nsimple"
        }
    }
    Rectangle {
        width: 200; height: 200
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            lineHeight: 1.5
            text: "Interligne\nde 150 %"
        }
    }
    Rectangle {
        width: 200; height: 200
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            lineHeight: 2
            text: "Interligne\ndouble"
        }
    }
}
