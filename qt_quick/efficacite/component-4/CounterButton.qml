import QtQuick 2.0

Rectangle {
    width: 150; height: 100
    border.color: "grey"
    signal incremented(int count)
    Text {
        font.pointSize: 16
        anchors.centerIn: parent
        text: "Cliquez ici"
    }
    MouseArea {
        property int count: 0
        anchors.fill: parent
        onClicked: {
            count = count + 1
            incremented(count)
        }
    }
}
