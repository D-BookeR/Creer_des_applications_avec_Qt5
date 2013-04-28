import QtQuick 2.0

Column {
    Repeater {
        model: [
            "<a href='http://cpp.developpez.com'>un lien</a>",
            "<pre>un texte préformaté</pre>",
            "des caractères spéciaux : &gt; &lt; &amp;",
            "<img src='logo.png' align='middle'>",
            "<ol><li>une ligne</li><li>une autre ligne</li></ol>",
            "<ul><li>une ligne</li><li>une autre ligne</li></ul>"
        ]

        delegate: Rectangle {
            width: 400; height: index > 2 ? 100 : 50
            Text {
                anchors.centerIn: parent
                textFormat: Text.StyledText
                font.pointSize: 16
                text: modelData
            }
        }
    }
}

