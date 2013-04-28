import QtQuick 2.0

Rectangle {
    width: 300; height: 200
    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.horizontalCenter
        anchors.margins: 10
        anchors.rightMargin: 5
        color: "lightgreen"
    }
    Rectangle {
        anchors.left: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 10
        anchors.leftMargin: 5
        color: "lightblue"
    }
}
