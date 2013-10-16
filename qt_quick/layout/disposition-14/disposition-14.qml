import QtQuick 2.0
import QtQuick.Layouts 1.0

GridLayout {
    rows: 4; columns: 4
    width: 200; height: 200
    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.columnSpan: 4
        color: "lightgreen"
        Text {
            anchors.centerIn: parent
            font.pointSize: 14
            text: "columnSpan: 4"
        }
    }
    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.rowSpan: 2
        color: "lightgreen"
        Text {
            anchors.centerIn: parent
            font.pointSize: 14
            text: "rowSpan: 2"
            rotation: 90
        }
    }
    Repeater {
        model: 6
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "lightblue"
            Text {
                anchors.centerIn: parent
                font.pointSize: 14
                text: index
            }
        }
    }
}
