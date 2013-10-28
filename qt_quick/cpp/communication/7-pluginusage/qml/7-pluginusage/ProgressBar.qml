import QtQuick 2.0

Rectangle {
    property int maximum: 100
    property int value: 0

    radius: 3
    border.width: 1
    border.color: "#d9d9d9"
    gradient: Gradient {
        GradientStop { position: 0; color: "#f0f0f0" }
        GradientStop { position: 1; color: "#e4e4e3" }
    }

    Rectangle {
        x: 1; y: 1
        width: (parent.value / parent.maximum * parent.width)
        height: parent.height - 2
        radius: 3
        smooth: true
        gradient: Gradient {
            GradientStop { position: 0; color: "#eeeeee" }
            GradientStop { position: 1; color: "#c0c0c0" }
        }
    }
}
