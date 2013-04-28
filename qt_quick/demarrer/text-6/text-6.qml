import QtQuick 2.0

Grid {
    x: 25; y: 25
    width: 475; height: 225
    columns: 2
    Text {
        width: 160; height: 50
        font.pointSize: 16
        horizontalAlignment: Text.AlignRight
        text: "Text.ElideNone : "
    }
    Text {
        font.pointSize: 16
        elide: Text.ElideNone
        text: "Un texte beaucoup trop long"
        Rectangle {
            border.color: "blue"
            color: "#110000FF"
            anchors.fill: parent
        }
    }

    Text {
        width: 160; height: 50
        font.pointSize: 16
        horizontalAlignment: Text.AlignRight
        text: "Text.ElideLeft : "
    }
    Text {
        width: 150
        font.pointSize: 16
        elide: Text.ElideLeft
        text: "Un texte beaucoup trop long"
        Rectangle {
            border.color: "blue"
            color: "#110000FF"
            anchors.fill: parent
        }
    }

    Text {
        width: 160; height: 50
        font.pointSize: 16
        horizontalAlignment: Text.AlignRight
        text: "Text.ElideMiddle : "
    }
    Text {
        width: 150
        font.pointSize: 16
        elide: Text.ElideMiddle
        text: "Un texte beaucoup trop long"
        Rectangle {
            border.color: "blue"
            color: "#110000FF"
            anchors.fill: parent
        }
    }

    Text {
        width: 160; height: 50
        font.pointSize: 16
        horizontalAlignment: Text.AlignRight
        text: "Text.ElideRight : "
    }
    Text {
        width: 150
        font.pointSize: 16
        elide: Text.ElideRight
        text: "Un texte beaucoup trop long"
        Rectangle {
            border.color: "blue"
            color: "#110000FF"
            anchors.fill: parent
        }
    }
}
