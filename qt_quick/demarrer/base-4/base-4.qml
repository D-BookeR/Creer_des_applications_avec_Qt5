import QtQuick 2.0

Row {
    width: 450; height: 100
    property color base: "blue"
    Rectangle {
        width: 150; height: 100
        color: Qt.lighter(base, 1.5)
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            text: "Lighter"
        }
    }
    Rectangle {
        width: 150; height: 100
        color: base
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            text: "Base"
        }
    }
    Rectangle {
        width: 150; height: 100
        color: Qt.darker(base, 1.5)
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            color: "white"
            text: "Darker"
        }
    }
}
