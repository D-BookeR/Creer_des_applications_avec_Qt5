import QtQuick 2.0

Rectangle {
    width: 100; height: 100
    color: "red"
    Text {
        anchors.centerIn: parent
        text: "Cliquez ici"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: console.log("Clique !")
    }
}
