import QtQuick 2.0

Rectangle {
    width: 360
    height: 360

    Text {
        anchors.centerIn: parent
        text: "Hello World"
        color: mouse.pressed ? "green" : "blue"
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
    }
}

