import QtQuick 2.0

Rectangle {
    width: 300; height: 300
    color: "salmon"
    Rectangle {
        x: 100; y: 100
        width: 100
        height: parent.height - 200
        color: "lightblue"
    }
}

