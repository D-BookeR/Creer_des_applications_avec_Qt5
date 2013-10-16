import QtQuick 2.0

Grid {
    x: 25; y: 25
    width: 700; height: 650
    rowSpacing: 25
    columnSpacing: 50
    columns: 2

    Text {
        font.pointSize: 16
        text: "Défaut"
    }

    Text {
        font.pointSize: 16
        text: "layoutDirection: Qt.RightToLeft"
    }

    Flow {
        spacing: 10
        width: 300
        Repeater {
            model: [ 50, 150, 100, 100, 50, 150, 100 ]
            delegate: Component {
                Rectangle {
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
    }

    Flow {
        spacing: 10
        width: 300
        layoutDirection: Qt.RightToLeft
        Repeater {
            model: [ 50, 150, 100, 100, 50, 150, 100 ]
            Rectangle {
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

    Text {
        font.pointSize: 16
        text: "flow: Flow.TopToBottom"
    }

    Text {
        font.pointSize: 16
        text: "layoutDirection: Qt.RightToLeft\nflow: Flow.TopToBottom"
    }

    Flow {
        spacing: 10
        width: 300; height: 300
        flow: Flow.TopToBottom
        Repeater {
            model: [ 50, 150, 100, 100, 50, 150, 100 ]
            Rectangle {
                width: modelData; height: 50
                color: "lightsalmon"
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
        width: 300; height: 300
        flow: Flow.TopToBottom
        layoutDirection: Qt.RightToLeft
        Repeater {
            model: [ 50, 150, 100, 100, 50, 150, 100 ]
            Rectangle {
                width: modelData; height: 50
                color: "gold"
                Text {
                    font.pointSize: 16
                    text: index
                    anchors.centerIn: parent
                }
            }
        }
    }
}

