import QtQuick 2.0

Rectangle {
    width: 325; height: 250

    Rectangle {
        x: 0; y:0
        width: 300; height: 200
        color: "lightsalmon"
        Text {
            anchors.centerIn: parent
            text: "Hello world"
            font.pointSize: 16
        }

        transform: [
            Rotation {
                angle: 45
                origin { x: 100; y: 100 }
                axis { x: 1; y: 1; z: 0 }
            },
            Scale {
                xScale: 0.8; yScale: 0.8
                origin { x: 100; y: 0 }
            },
            Translate {
                x: 25; y: 25
            }
        ]
    }
}
