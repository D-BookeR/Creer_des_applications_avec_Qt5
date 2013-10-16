import QtQuick 2.0

Rectangle {
    width: 220; height: 120
    Rectangle {
        id: rect1
        x: 10; y: 10
        width: (parent.width - 30) / 2
        height: parent.height - 20
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
        x: rect1.width + 20; y: 10
        width: (parent.width - 30) / 2
        height: parent.height - 20
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
