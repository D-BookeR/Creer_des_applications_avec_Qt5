import QtQuick 2.0

Grid {
    x: 25; y: 25
    width: 750; height: 250
    rowSpacing: 10
    columnSpacing: 25
    columns: 2

    Text {
        font.pointSize: 16
        text: "width: 400"
    }

    Text {
        font.pointSize: 16
        text: "width: 300"
    }

    Flow {
        spacing: 10
        width: 400
        Repeater {
            model: [ 50, 150, 100, 100, 50, 150, 100 ]
            delegate: Rectangle {
                width: modelData; height: 50
                color: "lightgreen"
                Text {
                    font.pointSize: 16
                    text: index
                    anchors.centerIn: parent
                }
            }
        }
    }

    Flow {
        spacing: 10
        width: 300
        Repeater {
            model: [ 50, 150, 100, 100, 50, 150, 100 ]
            delegate: Rectangle {
                width: modelData; height: 50
                color: "lightblue"
                Text {
                    font.pointSize: 16
                    text: index
                    anchors.centerIn: parent
                }
            }
        }
    }
}

