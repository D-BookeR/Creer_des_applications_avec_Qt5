import QtQuick 2.0

Rectangle {
    width: row.width + 20
    height: row.height + 20
    Row {
        id: row
        x: 10; y: 10
        spacing: 10

        Rectangle {
            width: 85
            height: 80
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
            width: 85
            height: 80
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
}
