import QtQuick 2.0

Rectangle {
    width: 50; height: 50
    MouseArea {
        anchors.fill: parent
        drag.target: parent
        drag.axis: Drag.YAxis
        drag.minimumX: 0
        drag.maximumX: parent.parent.parent.width - parent.width
        cursorShape: drag.active ? Qt.SizeAllCursor : Qt.ArrowCursor
    }
}
