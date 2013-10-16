import QtQuick 2.0
import QtQuick.Layouts 1.0

RowLayout {
    width: 200; height: 100

    Rectangle {
        color: "lightgreen"
        Layout.fillWidth: true
        Layout.fillHeight: true
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
        color: "lightblue"
        Layout.fillWidth: true
        Layout.fillHeight: true
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
