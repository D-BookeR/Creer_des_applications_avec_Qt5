import QtQuick 2.0

Row {
    Rectangle {
        width: 200; height: 200
        color: "lightsalmon"
        MouseArea {
            anchors.fill: parent
            onClicked: parent.opacity = 1 - parent.opacity
        }
    }
    Rectangle {
        width: 200; height: 200
        color: "lightblue"
        MouseArea {
            anchors.fill: parent
            onClicked: parent.visible = !parent.visible
        }
    }
}

