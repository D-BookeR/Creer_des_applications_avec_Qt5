import QtQuick 2.0

Rectangle {
    width: 200; height: 200
    Text {
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
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
        text: "hello world"
        font.pointSize: mouse.containsMouse ? 20 : 14
        color: mouse.pressed ? "red" : "black"
    }
}
