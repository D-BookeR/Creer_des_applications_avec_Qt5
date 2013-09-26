import QtQuick 2.0

Rectangle {
    width: 360
    height: 360

    Text {
        id: text
        anchors.centerIn: parent
        text: "Hello World"
        color: "blue"
    }

    MouseArea {
        anchors.fill: parent

        onPressed: text.color = "green"
        onReleased: text.color = "blue"
    }
}

