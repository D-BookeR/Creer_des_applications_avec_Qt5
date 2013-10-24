import QtQuick 2.0

Rectangle {
    width: 200; height: 100
    border.color: "black"
    radius: 10
    property alias text: label.text
    signal send()
    Text {
        id: label
        anchors.centerIn: parent
        font.pointSize: 16
    }
    MouseArea {
        anchors.fill: parent
        onClicked: parent.send()
    }
}
