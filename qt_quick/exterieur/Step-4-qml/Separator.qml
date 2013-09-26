import QtQuick 2.0

Item {
    width: parent.width - offset
    height: 1; x: offset / 2

    property string text: ""
    property int offset: 25

    Text {
        id: label
        text: parent.text
        color: "gray"
        renderType: Text.NativeRendering
        anchors {
            verticalCenter: parent.verticalCenter
            verticalCenterOffset: -2
        }
    }

    Rectangle {
        color: "gray"
        height: parent.height
        anchors {
            left: label.right
            right: parent.right
            leftMargin: parent.text !== "" ? 5 : 0
        }
    }
}
