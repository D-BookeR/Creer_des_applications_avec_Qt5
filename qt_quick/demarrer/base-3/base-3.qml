import QtQuick 2.0

Rectangle {
    width: 400; height: 400
    Rectangle {
        id: monRectangle
        x: 100; y: 100
        color: "lightblue"
        height: parent.height - 150
        width: 200
    }
    Rectangle {
        x: 50; y: 50
        color: "lightgreen"
        height: monRectangle.height - 50
        width: parent.width - 100
    }
}
