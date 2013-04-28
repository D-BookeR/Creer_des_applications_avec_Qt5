import QtQuick 2.0

Rectangle {
    property int mode
    property string label
    width: 200
    height: 350

    Image {
        id: image
        width: parent.width; height: parent.height - textItem.height
        source: "logo.png"
        fillMode: mode
    }

    Rectangle {
        anchors.fill: image
        border.color: "lightgrey"
        color: "#00000000"
    }

    Text {
        id: textItem
        anchors.top: image.bottom
        anchors.horizontalCenter: image.horizontalCenter
        text: label
        font.pointSize: 16
    }
}
