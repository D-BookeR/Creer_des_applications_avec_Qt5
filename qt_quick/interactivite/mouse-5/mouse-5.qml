import QtQuick 2.0

Rectangle {
    width: 200; height: 200
    ButtonBar {
        id: buttons
        width: 50
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }
    CentralArea {
        anchors.right: parent.right
        anchors.left: buttons.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }
}
