import QtQuick 2.0

Column {
    Rectangle {
        width: 500; height: 75
        Rectangle {
            anchors.centerIn: parent
            width: 200; height: 50
            color: "lightgreen"
            Input {
            }
        }
    }

    Rectangle {
        width: 500; height: 75
        Rectangle {
            anchors.centerIn: parent
            width: 200; height: 50
            color: "lightgreen"
            Input {
                width: parent.width
                autoScroll: true
            }
        }
    }
}
