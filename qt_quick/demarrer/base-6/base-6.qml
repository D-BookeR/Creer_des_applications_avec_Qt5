import QtQuick 2.0

Rectangle {
    width: 150; height: 300
    gradient: Gradient {
        stops: [
            GradientStop { position:   0/360; color: "red" },
            GradientStop { position:  60/360; color: "yellow" },
            GradientStop { position: 120/360; color: "green" },
            GradientStop { position: 180/360; color: "cyan" },
            GradientStop { position: 240/360; color: "blue" },
            GradientStop { position: 300/360; color: "magenta" },
            GradientStop { position: 360/360; color: "red" }
        ]
    }
}

