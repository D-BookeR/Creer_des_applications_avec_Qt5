import QtQuick 2.0

Item {
    width: Math.floor(grid.width / 2) - Math.floor(grid.spacing / 2)
    height: 60

    Rectangle {
        anchors.fill: parent
        radius: 10
        border.color: "gray"
        border.width: 1
        gradient: Gradient {
            GradientStop { position: 0; color: "#222222" }
            GradientStop { position: 0.8; color: "#111111" }
        }
    }

    Text {
        id: header
        text: city
        color: "white"
        font.bold: true
        font.pixelSize: 14
        renderType: Text.NativeRendering
        elide: Text.ElideRight
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            leftMargin: 15
            rightMargin: 15
            topMargin: 10
        }
    }

    Text {
        text: date
        color: "gray"
        font.bold: true
        font.pixelSize: 12
        renderType: Text.NativeRendering
        elide: Text.ElideRight
        anchors {
            left: parent.left
            right: parent.right
            top: header.bottom
            leftMargin: 15
            rightMargin: 15
            topMargin: 5
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: setCurrentSearch(city);
    }
}
