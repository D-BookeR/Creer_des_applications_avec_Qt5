import QtQuick 2.1

Rectangle {
    width: 300; height: 300

    DropArea {
        x: 210; y: 10
        width: 50; height: 50
        onDropped: console.debug("onDropped")
        keys: "blue"
        Rectangle {
            anchors.fill: parent
            border.color: parent.containsDrag ? "darkgrey" : "lightgrey"
            color: parent.containsDrag ? "lightgrey" : "white"
        }
    }
    DropArea {
        x: 210; y: 210
        width: 50; height: 50
        onDropped: console.debug("onDropped")
        keys: "red"
        Rectangle {
            anchors.fill: parent
            border.color: parent.containsDrag ? "darkgrey" : "lightgrey"
            color: parent.containsDrag ? "lightgrey" : "white"
        }
    }
    Rectangle {
        x: 10; y: 210
        width: 50; height: 50
        color: "blue"
        Drag.active: mouseArea.drag.active
        Drag.keys: "blue"
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            drag.target: parent
            onReleased: parent.Drag.drop()
            onPressed: parent.Drag.hotSpot = Qt.point(mouse.x, mouse.y)
        }
    }
    Rectangle {
        x: 10; y: 10
        width: 50; height: 50
        color: "red"
        Drag.active: mouseArea2.drag.active
        Drag.keys: "red"
        MouseArea {
            id: mouseArea2
            anchors.fill: parent
            drag.target: parent
            onReleased: parent.Drag.drop()
            onPressed: parent.Drag.hotSpot = Qt.point(mouse.x, mouse.y)
        }
    }
}
