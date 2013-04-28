import QtQuick 2.0

Rectangle {
    width: 600; height: 400
    Rectangle {
        x: 50; y: 50
        width: (parent.width - 150) / 2
        height: parent.height - 100
        color: "lightgreen"
    }
    Rectangle {
        x: width + 100; y: 50
        width: (parent.width - 150) / 2
        height: parent.height - 100
        color: "lightblue"
    }
}

