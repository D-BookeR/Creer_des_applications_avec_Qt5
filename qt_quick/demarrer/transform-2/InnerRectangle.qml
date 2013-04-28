import QtQuick 2.0

Rectangle {
    x: 50; y: 50
    width: 100; height: 100
    property int xCenter: 0
    property int yCenter: 0
    property alias text: label.text
    color: "lightsalmon"
    rotation: 25
    Text {
        id: label
        anchors.centerIn: parent
        font.pointSize: 16
    }
    Rectangle {
        color: "red"
        radius: 5
        width: 10; height: 10
        x: (xCenter * 50) - 5
        y: (yCenter * 50) - 5
    }
}
