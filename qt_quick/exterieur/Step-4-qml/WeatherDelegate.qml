import QtQuick 2.0

Rectangle {
    id: delegate
    height: 90
    radius: 10
    border.color: "gray"
    border.width: 1
    gradient: Gradient {
        GradientStop { position: 0; color: "#222222" }
        GradientStop { position: 0.8; color: "#111111" }
    }

    property string dateStr: ""
    property string temperature: ""

    Row {
        spacing: 20
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            margins: 15
        }

        Image {
            id: iconImg
            source: icon
            anchors.verticalCenter: parent.verticalCenter
            width: 64; height: 64
            Rectangle {
                anchors.fill: parent
                anchors.margins: -1
                radius: 2
                clip: true
                color: "transparent"
                border.width: 2
                border.color: "gray"
                visible: parent.status === Image.Ready
            }
        }

        Column {
            spacing: 6
            anchors {
                top: parent.top
                bottom: parent.bottom
            }
            Text {
                id: titleText
                text: delegate.dateStr
                color: "white"
                font.bold: true
                font.pixelSize: 16
                renderType: Text.NativeRendering
            }
            Text {
                text: desc
                color: "gray"
                font.bold: true
                font.pixelSize: 12
                renderType: Text.NativeRendering
                width: titleText.width
                elide: Text.ElideRight
            }
            Text {
                text: delegate.temperature
                color: "gray"
                font.bold: true
                font.pixelSize: 12
                renderType: Text.NativeRendering
            }
        }

        VSeparator { offset: 0 }

        Column {
            spacing: 6
            anchors {
                top: parent.top
                bottom: parent.bottom
            }
            Text {
                text: "About the wind"
                color: "white"
                font.bold: true
                font.pixelSize: 16
                renderType: Text.NativeRendering
            }
            Text {
                text: "From " + winddir
                color: "gray"
                font.bold: true
                font.pixelSize: 12
                renderType: Text.NativeRendering
            }
            Text {
                text: windspeed + " km/h"
                color: "gray"
                font.bold: true
                font.pixelSize: 12
                renderType: Text.NativeRendering
            }
        }
    }
}
