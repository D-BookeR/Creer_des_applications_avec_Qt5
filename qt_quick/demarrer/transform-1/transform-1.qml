import QtQuick 2.0

Grid {
    columns: 2
    Rectangle {
        width: 300; height: 200
        Rectangle {
            width: 200; height: 100
            anchors.centerIn: parent
            color: "lightgrey"
            Text {
                text: "aucune\ntransformation"
                anchors.centerIn: parent
                font.pointSize: 16
            }
        }
    }

    Rectangle {
        width: 350; height: 200
        Rectangle {
            width: 200; height: 100
            anchors.centerIn: parent
            color: "lightgreen"
            scale: 1.25
            Text {
                text: "scale: 1.25"
                anchors.centerIn: parent
                font.pointSize: 16
            }
        }
    }

    Rectangle {
        width: 300; height: 300
        Rectangle {
            width: 200; height: 100
            anchors.centerIn: parent
            color: "lightsalmon"
            rotation: 30
            Text {
                text: "rotation: 30"
                anchors.centerIn: parent
                font.pointSize: 16
            }
        }
    }

    Rectangle {
        width: 350; height: 300
        Rectangle {
            width: 200; height: 100
            anchors.centerIn: parent
            color: "lightblue"
            rotation: 30
            scale: 1.25
            Text {
                text: "rotation: 30\nscale: 1.25"
                anchors.centerIn: parent
                font.pointSize: 16
            }
        }
    }
}

