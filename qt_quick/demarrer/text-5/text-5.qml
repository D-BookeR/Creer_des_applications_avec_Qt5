import QtQuick 2.0

Row {
    Rectangle {
        width: 200; height: 200
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            textFormat: Text.StyledText
            text: "Text.StyledText :<br><br>naaaaa<br>bbbbb\nccccc<br>\nddddd"
        }
    }
    Rectangle {
        width: 250; height: 200
        Text {
            anchors.centerIn: parent
            font.pointSize: 16
            textFormat: Text.PlainText
            text: "Text.PlainText :\n\naaaaa<br>bbbbb\nccccc<br>\nddddd"
        }
    }
}

