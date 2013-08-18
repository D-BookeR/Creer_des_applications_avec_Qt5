import QtQuick 2.0

Rectangle {
    width: 150; height: 75
    property alias text: label.text
    Text {
        id: label
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        font.pointSize: 14
    }
}
