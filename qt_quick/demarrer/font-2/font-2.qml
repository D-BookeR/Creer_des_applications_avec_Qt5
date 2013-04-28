import QtQuick 2.0

Column {
    width: 800; height: 375
    Rectangle {
        width: 800; height: 75
        Text {
            anchors.centerIn: parent
            font.family: "Times New Roman"
            font.pointSize: 20
            text: "Texte affiché en utilisant la police 'Times New Roman'"
        }
    }
    Rectangle {
        width: 800; height: 75
        Text {
            anchors.centerIn: parent
            font.family: "Arial"
            font.pointSize: 20
            text: "Texte affiché en utilisant la police 'Arial'"
        }
    }
    Rectangle {
        width: 800; height: 75
        Text {
            anchors.centerIn: parent
            font.family: "Symbol"
            font.pointSize: 20
            text: "Texte affiché en utilisant la police 'Symbol'"
        }
    }
    Rectangle {
        width: 800; height: 75
        Text {
            anchors.centerIn: parent
            font.family: "Comic Sans MS"
            font.pointSize: 20
            text: "Texte affiché en utilisant la police 'Comic Sans MS'"
        }
    }
    Rectangle {
        width: 800; height: 75
        Text {
            anchors.centerIn: parent
            font.family: "Courier"
            font.pointSize: 20
            text: "Texte affiché en utilisant la police 'Courier'"
        }
    }
}
