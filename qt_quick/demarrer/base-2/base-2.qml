import QtQuick 2.0

Rectangle {
    width: 500; height: 500
    Rectangle {
        x: 50; y: 50
        width: 300; height: 300
        color: "lightgreen"
        Rectangle {
            x: 100; y: 100
            width: 300; height: 300
            color: "lightblue"
        }
    }
}
