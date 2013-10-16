import QtQuick 2.0

Rectangle {
    width: grid.width + 20
    height: grid.height + 20
    Grid {
        id: grid
        x: 10; y: 10
        columns: 2
        Text {
            width: 130; height: 30
            font.pointSize: 14
            text: "En colonne"
        }
        Text {
            width: 130; height: 30
            font.pointSize: 14
            text: "En grille"
        }
        Column {
            spacing: 5
            Repeater {
                model: 4
                delegate:
                    Rectangle {
                    width: 30; height: 30
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
            spacing: 5
            Repeater {
                model: 16
                delegate:
                    Rectangle {
                    width: 30; height: 30
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
