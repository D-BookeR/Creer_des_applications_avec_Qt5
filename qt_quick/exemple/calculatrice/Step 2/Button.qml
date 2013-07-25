import QtQuick 2.0

Item {
    property alias text: textItem.text

    width: 30
    height: 50

    Text {
        id: textItem
        font.pixelSize: 48
        lineHeight: 0.75
        color: "white"
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: console.log(parent.text)
    }
}
