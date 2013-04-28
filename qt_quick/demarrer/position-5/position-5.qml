import QtQuick 2.0

Grid {
    x: 25; y: 25
    width: 850; height: 725
    rowSpacing: 25
    columnSpacing: 50
    columns: 2

    Text {
        font.pointSize: 16
        text: "Défaut"
    }

    Text {
        font.pointSize: 16
        text: "rows: 2"
    }

    Grid {
        spacing: 10
        Repeater {
            model: 6
            Rectangle {
                width: 100; height: 100
                color: "lightgreen"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
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
                width: 100; height: 100
                color: "lightblue"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
                    text: index
                }
            }
        }
    }

    Text {
        font.pointSize: 16
        text: "\ncolumns: 2"
    }

    Text {
        font.pointSize: 16
        text: "\nrows: 2 - columns: 2"
    }

    Grid {
        spacing: 10
        columns: 2
        Repeater {
            model: 6
            Rectangle {
                width: 100; height: 100
                color: "lightsalmon"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
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
                width: 100; height: 100
                color: "gold"
                Text {
                    anchors.centerIn: parent
                    font.pointSize: 16
                    text: index
                }
            }
        }
    }
}
