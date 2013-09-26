import QtQuick 2.0

Rectangle {
    id: button
    width: textArea.width + 15; height: 28
    opacity: enabled ? 1 : 0.6
    radius: enabled ? 10 : 5
    border.color: "#353535"
    border.width: 1
    gradient: Gradient {
        GradientStop { position: 0; color: !mouseArea.pressed ? "#222222" : "#151515" }
        GradientStop { position: 0.8; color: !mouseArea.pressed ? "#111111" : "222222" }
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
        color: "darkgray"
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: parent.clicked();
        onPressed: parent.pressed();
        onReleased: parent.released();
    }
}
