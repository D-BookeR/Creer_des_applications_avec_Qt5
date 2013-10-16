import QtQuick 2.0
import QtQuick.Layouts 1.0

Row {
//RowLayout {
    width: 200; height: 100

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
