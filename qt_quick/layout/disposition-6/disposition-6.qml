import QtQuick 2.0

Grid {
    x: 10; y: 10
    width: 290; height: 300
    columnSpacing: 10
    columns: 2

    Text {
        width: 130; height: 30
        font.pointSize: 14
        text: "Défaut"
    }

    Text {
        width: 130; height: 30
        font.pointSize: 14
        text: "rows: 2"
    }

    Grid {
        spacing: 10
        Repeater {
            model: 6
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
        spacing: 10
        rows: 2
        Repeater {
            model: 6
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

    Text {
        font.pointSize: 14
        text: "\n\ncolumns: 2"
    }

    Text {
        font.pointSize: 14
        text: "\nrows: 2\ncolumns: 2"
    }

    Grid {
        spacing: 10
        columns: 2
        Repeater {
            model: 6
            Rectangle {
                width: 30; height: 30
                color: "lightsalmon"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 14
                    text: index
                }
            }
        }
    }

    Grid {
        spacing: 10
        rows: 2; columns: 2
        Repeater {
            model: 6
            Rectangle {
                width: 30; height: 30
                color: "gold"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 14
                    text: index
                }
            }
        }
    }
}
