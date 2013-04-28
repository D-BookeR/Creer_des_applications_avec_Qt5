import QtQuick 2.0

Rectangle {
    width: 500; height: 500

    Rectangle {
        x: 100; y: 0
        width: 100; height: 200
        color: "lightgreen"
        Text {
            text: "z = " + parent.z
            font.pointSize: 16
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle {
        x: 300; y: 0
        width: 100; height: 200
        color: "darkgreen"
        z: 1
        Text {
            text: "z = " + parent.z
            font.pointSize: 16
            color: "white"
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle {
        x: 0; y: 100
        width: 500; height: 300
        color: "lightsalmon"
        Text {
            text: "z = " + parent.z
            font.pointSize: 16
            anchors.centerIn: parent
        }
    }

    Rectangle {
        x: 100; y: 300
        width: 100; height: 200
        color: "lightblue"
        Text {
            text: "z = " + parent.z
            font.pointSize: 16
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle {
        x: 300; y: 300
        width: 100; height: 200
        color: "darkblue"
        z: 1
        Text {
            text: "z = " + parent.z
            font.pointSize: 16
            color: "white"
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}


