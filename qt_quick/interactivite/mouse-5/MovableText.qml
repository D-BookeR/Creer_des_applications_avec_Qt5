import QtQuick 2.0

Text {
    id: label
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
        drag.target: parent
        drag.axis: Drag.XandYAxis
        drag.minimumX: 0
        drag.maximumX: parent.parent.width - parent.width
        drag.minimumY: 0
        drag.maximumY: parent.parent.height - parent.height
    }
    text: "hello world"
    font.pointSize: 14
}
