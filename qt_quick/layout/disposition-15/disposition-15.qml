import QtQuick 2.0

Grid {
    rows: 3; columns: 3
    spacing: 4
    Repeater {
        model: 9
        Rectangle {
            width: 50; height: 50
            color: "lightgreen"
            Text {
                anchors.centerIn: parent
                font.pointSize: 14
                text: "(" +
                      parent.Positioner.index % 3 + "," +
                      Math.floor(parent.Positioner.index / 3) + ")"

            }
        }
    }
}
