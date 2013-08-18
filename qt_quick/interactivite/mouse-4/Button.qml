import QtQuick 2.0

Rectangle {
    width: 50; height: 50
    MouseArea {
        anchors.fill: parent
        onClicked: label.color = color
    }
}
