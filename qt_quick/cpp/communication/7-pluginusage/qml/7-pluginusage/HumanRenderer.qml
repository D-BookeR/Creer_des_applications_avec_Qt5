import QtQuick 2.0
import Human 1.0

Column {
    property Human ref

    Rectangle {
        id: rect
        width: infos.width + 35
        height: infos.height + 35
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 3
        border.width: 1
        border.color: "#d9d9d9"
        gradient: Gradient {
            GradientStop { position: 0; color: "#f0f0f0" }
            GradientStop { position: 1; color: "#e4e4e3" }
        }

        Text {
            id: infos
            text: "Name: " + ref.name + "\nHP: " + ref.hp + " / 100"
            horizontalAlignment: Text.AlignHCenter
            renderType: Text.NativeRendering
            anchors.centerIn: parent
        }
    }

    Rectangle {
        width: 1
        height: 15
        color: "#d9d9d9"
        anchors.horizontalCenter: rect.horizontalCenter
    }

    ProgressBar {
        width: 125
        height: 25
        value: ref.hp
        maximum: 100
        anchors.horizontalCenter: rect.horizontalCenter
    }
}
