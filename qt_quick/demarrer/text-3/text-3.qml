import QtQuick 2.0

Column {
    Repeater {
        model: [
            "<h1>un titre de niveau 1</h1>",
            "<h2>un titre de niveau 2</h2>",
            "<h3>un titre de niveau 3</h3>",
            "<h4>un titre de niveau 4</h4>",
            "<h5>un titre de niveau 5</h5>",
            "<h6>un titre de niveau 6</h6>"
        ]

        delegate: Rectangle {
            width: 500; height: index == 0 ? 75 : 50
            Text {
                anchors.centerIn: parent
                textFormat: Text.StyledText
                font.pointSize: 16
                text: modelData
            }
        }
    }
}

