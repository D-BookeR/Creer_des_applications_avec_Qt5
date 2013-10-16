import QtQuick 2.0

Rectangle {
    width: grid.width + 20
    height: grid.height + 20
    Grid {
        id: grid
        x: 10; y: 10
        columnSpacing: 20
        columns: 2
        Text {
            width: 40; height: 30
            font.pointSize: 14
            text: "LeftToRight"
        }
        Text {
            width: 40; height: 30
            font.pointSize: 14
            text: "TopToBottom"
        }

        Grid {
            rows: 3; columns: 3
            spacing: 5
            Repeater {
                model: 9
                Rectangle {
                    width: 40; height: 30
                    color: "lightgreen"
                    Text {
                        anchors.centerIn: parent
                        font.pointSize: 14
                        text: index
                    }
                }
            }
        }

        Grid {
            rows: 3; columns: 3
            spacing: 5
            flow: Grid.TopToBottom
            Repeater {
                model: 9
                Rectangle {
                    width: 40; height: 30
                    color: "lightblue"
                    Text {
                        anchors.centerIn: parent
                        font.pointSize: 14
                        text: index
                    }
                }
            }
        }
    }
}
