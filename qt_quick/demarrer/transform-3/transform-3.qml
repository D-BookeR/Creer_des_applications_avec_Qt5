import QtQuick 2.0

Rectangle {
    width: 600
    height: 360

    Rectangle {
        id: smoothRect
        x: 25; y: 25
        width: 75; height: 75
        color: "salmon"
        rotation: 10
    }

    Text {
        anchors.top: smoothRect.bottom
        anchors.horizontalCenter: smoothRect.horizontalCenter
        anchors.margins: 10
        text: "antialiasing: false"
        font.pixelSize: 14
    }

    Rectangle {
        id: noSmoothRect
        x: 250; y: 25
        width: 75; height: 75
        color: "salmon"
        rotation: 10
        antialiasing: true
    }

    Text {
        anchors.top: noSmoothRect.bottom
        anchors.horizontalCenter: noSmoothRect.horizontalCenter
        anchors.margins: 10
        text: "antialiasing: true"
        font.pixelSize: 14
    }

    Image {
        id: smoothImage
        x: 25; y: 150
        source: "logo.png"
        rotation: 10
        smooth: false
    }

    Text {
        anchors.top: smoothImage.bottom
        anchors.horizontalCenter: smoothImage.horizontalCenter
        anchors.margins: 10
        text: "smooth: false"
        font.pixelSize: 14
    }

    Image {
        id: noSmoothImage
        x: 250; y: 150
        source: "logo.png"
        rotation: 10
        smooth: true
    }
    Text {
        anchors.top: noSmoothImage.bottom
        anchors.horizontalCenter: noSmoothImage.horizontalCenter
        anchors.margins: 10
        text: "smooth: true"
        font.pixelSize: 14
    }
}

