import QtQuick 2.0

Column {
    Repeater {
        model: [
            "<b>un texte en gras</b>",
            "<i>un texte en italique</i>",
            "<p>un paragraphe</p>",
            "<u>un texte souligné</u>",
            "<font color='red'>un texte en rouge</font>",
            "<font size='1'>un texte de taille 1</font>",
            "<font size='2'>un texte de taille 2</font>",
            "<font size='3'>un texte de taille 3</font>",
            "<font size='4'>un texte de taille 4</font>",
            "<font size='5'>un texte de taille 5</font>",
            "<font size='6'>un texte de taille 6</font>",
            "<font size='7'>un texte de taille 7</font>"
        ]

        delegate: Rectangle {
            width: 500; height: index == 11 ? 75 : 50
            Text {
                anchors.centerIn: parent
                textFormat: Text.StyledText
                font.pointSize: 16
                text: modelData
            }
        }
    }
}
