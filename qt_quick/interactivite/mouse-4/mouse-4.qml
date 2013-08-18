import QtQuick 2.0

Rectangle {
    width: 200; height: 150
    ButtonBar {
        id: buttons
        width: 50
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }
    CustomText {
        id: label
    }
}
