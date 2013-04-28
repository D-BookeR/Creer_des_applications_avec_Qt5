import QtQuick 2.0

Rectangle {
    width: 700; height: 300

    Rectangle {
        x: 0; y: 100
        width: 700; height: 200
        color: "lightsalmon"
        z: 1
        Text {
            text: "z = " + parent.z
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 16
        }

        Rectangle {
            x: 100; y: -100
            width: 100; height: 200
            color: "lightgreen"
            z: -1
            Text {
                text: "z = " + parent.z
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 16
            }
        }

        Rectangle {
            x: 300; y: -100
            width: 100; height: 200
            color: "limegreen"
            Text {
                text: "z = " + parent.z
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 16
            }
        }

        Rectangle {
            x: 500; y: -100
            width: 100; height: 200
            color: "darkgreen"
            z: 1
            Text {
                text: "z = " + parent.z
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 16
                color: "white"
            }
        }
    }
}


