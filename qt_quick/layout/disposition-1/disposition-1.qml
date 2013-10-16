import QtQuick 2.0

Rectangle {
    width: 200; height: 100
    Rectangle {
        x: 10; y: 10
        width: 85; height: 80
        color: "lightgreen"
        Text {
            anchors.centerIn: parent
            text: "x = "  + parent.x + "\n" +
                  "y = "  + parent.y + "\n" +
                  "width = "  + parent.width + "\n" +
                  "height = "  + parent.height
            font.pointSize: 12
        }
    }
    Rectangle {
        x: 105; y: 10
        width: 85; height: 80
        color: "lightblue"
        Text {
            anchors.centerIn: parent
            text: "x = "  + parent.x + "\n" +
                  "y = "  + parent.y + "\n" +
                  "width = "  + parent.width + "\n" +
                  "height = "  + parent.height
            font.pointSize: 12
        }
    }
}

