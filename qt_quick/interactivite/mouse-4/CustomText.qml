import QtQuick 2.0

Text {
    x: (parent.width + 50) / 2 - width / 2
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
    font.pointSize: 14
}
