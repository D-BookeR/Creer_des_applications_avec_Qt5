import QtQuick 2.1

Grid {
    spacing: 5
    Rectangle {
        width: 100; height: 100
        border.color: "grey"
        color: "#000000ff"
        Grid {
            z: -1
            rows: 2; columns: 1
            horizontalItemAlignment: Grid.AlignLeft
            Rectangle {
                width: 50; height: 50
                color: "lightgreen"
            }
            Rectangle {
                width: 100; height: 50
                color: "lightblue"
            }
        }
    }
    Rectangle {
        width: 100; height: 100
        border.color: "grey"
        color: "#000000ff"
        Grid {
            z: -1
            rows: 2; columns: 1
            horizontalItemAlignment: Grid.AlignHCenter
            Rectangle {
                width: 50; height: 50
                color: "lightgreen"
            }
            Rectangle {
                width: 100; height: 50
                color: "lightblue"
            }
        }
    }
    Rectangle {
        width: 100; height: 100
        border.color: "grey"
        color: "#000000ff"
        Grid {
            z: -1
            rows: 2; columns: 1
            horizontalItemAlignment: Grid.AlignRight
            Rectangle {
                width: 50; height: 50
                color: "lightgreen"
            }
            Rectangle {
                width: 100; height: 50
                color: "lightblue"
            }
        }
    }
}
