import QtQuick 2.0

Rectangle {
    width: 200; height: 200
    Text {
        property int lastX: parent.width / 2 - width / 2
        property int lastY: parent.height / 2 - height / 2
        x: {
            if (mouse.pressed)
                lastX = mouse.mouseX - width / 2
            else
                return lastX
        }
        y: {
            if (mouse.pressed)
                lastY = mouse.mouseY - height / 2
            else
                return lastY
        }
        text: "hello world"
        font.pointSize: mouse.containsMouse ? 20 : 14
        color: mouse.pressed ? "red" : "black"
    }
    MouseArea {
        id: mouse
        anchors.fill: parent
        acceptedButtons: Qt.AllButtons
        hoverEnabled: true
        cursorShape: {
            if (pressed) {
                if (pressedButtons & Qt.LeftButton)
                    Qt.ClosedHandCursor
                else
                    Qt.ForbiddenCursor
            }
            else
                Qt.OpenHandCursor
        }
    }
}
