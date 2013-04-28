import QtQuick 2.0

Column {
    width: 600; height: 375
    Rectangle {
        width: 600; height: 75
        Text {
            anchors.centerIn: parent
            font.pointSize: 20
            font.weight: Font.Light
            text: "Texte affiché en utilisant Font.Light"
        }
    }
    Rectangle {
        width: 600; height: 75
        Text {
            anchors.centerIn: parent
            font.pointSize: 20
            font.weight: Font.Normal
            text: "Texte affiché en utilisant Font.Normal"
        }
    }
    Rectangle {
        width: 600; height: 75
        Text {
            anchors.centerIn: parent
            font.pointSize: 20
            font.weight: Font.DemiBold
            text: "Texte affiché en utilisant Font.DemiBold"
        }
    }
    Rectangle {
        width: 600; height: 75
        Text {
            anchors.centerIn: parent
            font.pointSize: 20
            font.weight: Font.Bold
            text: "Texte affiché en utilisant Font.Bold"
        }
    }
    Rectangle {
        width: 600; height: 75
        Text {
            anchors.centerIn: parent
            font.pointSize: 20
            font.weight: Font.Black
            text: "Texte affiché en utilisant Font.Black"
        }
    }
}
