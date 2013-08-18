import QtQuick 2.0

Rectangle {
    width: 220; height: 75
    property int count: 0
    Text {
        font.pointSize: 16
        anchors.centerIn: parent
        text: "Nombre de clics : " + count
    }
    MouseArea {
        anchors.fill: parent
        onClicked: count = count + 1
    }
}

