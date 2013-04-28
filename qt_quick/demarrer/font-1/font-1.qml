import QtQuick 2.0

Column {
    width: 700; height: 375
    Rectangle {
        width: 700; height: 75
        Text {
            anchors.centerIn: parent
            font.capitalization: Font.MixedCase
            font.pointSize: 20
            text: "Texte affiché en utilisant Font.MixedCase"
        }
    }
    Rectangle {
        width: 700; height: 75
        Text {
            anchors.centerIn: parent
            font.capitalization: Font.AllUppercase
            font.pointSize: 20
            text: "Texte affiché en utilisant Font.AllUppercase"
        }
    }
    Rectangle {
        width: 700; height: 75
        Text {
            anchors.centerIn: parent
            font.capitalization: Font.AllLowercase
            font.pointSize: 20
            text: "Texte affiché en utilisant Font.AllLowercase"
        }
    }
    Rectangle {
        width: 700; height: 75
        Text {
            anchors.centerIn: parent
            font.capitalization: Font.SmallCaps
            font.pointSize: 20
            text: "Texte affiché en utilisant Font.SmallCaps"
        }
    }
    Rectangle {
        width: 700; height: 75
        Text {
            anchors.centerIn: parent
            font.capitalization: Font.Capitalize
            font.pointSize: 20
            text: "Texte affiché en utilisant Font.Capitalize"
        }
    }
}
