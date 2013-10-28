import QtQuick 2.0

Rectangle {
    id: button
    width: textArea.width + 35; height: 35
    opacity: enabled ? 1 : 0.6
    radius: enabled ? 5 : 2
    border.color: "#505050"
    border.width: 1
    gradient: Gradient {
        GradientStop { position: 0; color: !mouseArea.pressed ? "#444444" : "#151515" }
        GradientStop { position: 0.8; color: !mouseArea.pressed ? "#222222" : "222222" }
    }

    property alias text: textArea.text
    signal clicked()
    signal pressed()
    signal released()

    Text {
        id: textArea
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        renderType: Text.NativeRendering
        color: "white"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: parent.clicked();
        onPressed: parent.pressed();
        onReleased: parent.released();
    }
}
