import QtQuick 2.0

Column {
    Row {
        Column {
            MouseArea {
                width: 150; height: 50
                onClicked: greenRect.visible = !greenRect.visible
                Text {
                    text: "Cliquez ici"
                    font.pointSize: 16
                    anchors.centerIn: parent
                    Rectangle {
                        z: -1
                        anchors.fill: parent
                        color: "lightgreen"
                    }
                }
            }
            MouseArea {
                width: 150; height: 50
                onClicked: salmonRect.visible = !salmonRect.visible
                Text {
                    text: "Cliquez ici"
                    font.pointSize: 16
                    anchors.centerIn: parent
                    Rectangle {
                        z: -1
                        anchors.fill: parent
                        color: "lightsalmon"
                    }
                }
            }
        }
        Rectangle {
            id: greenRect
            width: 200; height: 200
            color: "lightgreen"

            Rectangle {
                id: salmonRect
                x: 50; y: 50
                width: 100; height: 100
                color: "lightsalmon"
            }
        }
    }
    Rectangle {
        width: 300; height: 75
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            text: salmonRect.visible ?
                      "Le rectangle couleur saumon\nest visible" :
                      "Le rectangle couleur saumon\nn'est pas visible"
        }
    }
}

