import QtQuick 2.0

Rectangle {
    width: 375
    height: 250

    Rectangle {
        id: noClippedImage
        x:25; y: 25
        width: 100; height: 100
        Image {
            width: 200; height: 200
            source: "logo.png"
        }
    }

    Rectangle {
        x:25; y: 25
        width: 100; height: 100
        color: "#00000000"
        border.color: "black"
    }

    Text {
        text: "clip: false"
        font.pixelSize: 20
        anchors.horizontalCenter: noClippedImage.horizontalCenter
    }

    Rectangle {
        id: clippedImage
        x:225; y: 25
        width: 100; height: 100
        clip:true
        Image {
            width: 200; height: 200
            source: "logo.png"
        }
    }

    Rectangle {
        x:225; y: 25
        width: 100; height: 100
        color: "#00000000"
        border.color: "black"
    }

    Text {
        text: "clip: true"
        font.pixelSize: 20
        anchors.horizontalCenter: clippedImage.horizontalCenter
    }
}

