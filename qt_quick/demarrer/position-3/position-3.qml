import QtQuick 2.0

Row {
    x: 50; y: 50
    width: 600; height: 400
    spacing: 50
    Rectangle {
        width: (parent.width - 150) / 2
        height: parent.height - 100
        color: "lightgreen"
    }
    Rectangle {
        width: (parent.width - 150) / 2
        height: parent.height - 100
        color: "lightblue"
    }
}
