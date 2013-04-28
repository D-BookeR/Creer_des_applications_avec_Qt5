import QtQuick 2.0

Rectangle {
    property var source

    Text {
        id: label
        anchors.centerIn: parent
        font.pointSize: 16
        visible: image.status != Image.Ready
        text: {
            switch (image.status) {
            case Image.Null: "No source"; break;
            case Image.Ready: "Image ready"; break;
            case Image.Loading: "Loading in progress"; break;
            case Image.Error: "Loading error"; break;
            }
        }
    }

    Rectangle {
        anchors.top: label.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: label.horizontalCenter
        width: 100; height: 6
        color: "#CCCCFF"
        border.color: "#8888FF"
        visible: image.status == Image.Loading
        Rectangle {
            x: 1; y: 1
            height: parent.height - 2
            width: (parent.width - 2) * image.progress
            color: "#33FF0000"
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: image.source = source
    }

    Image {
        id: image
        anchors.fill: parent
    }
}
