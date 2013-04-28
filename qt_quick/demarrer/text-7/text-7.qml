import QtQuick 2.0

Rectangle {
    width: 525; height: 225
    property string text: "Une première ligne très très longue.\x9C" +
                          "Une seconde ligne courte.\x9C" +
                          "Une ligne courte."

    Text {
        x: 25; y: 25
        width: 160;
        font.pointSize: 16
        horizontalAlignment: Text.AlignRight
        text: "Largeur de 300 :"
    }
    Text {
        x: 200; y: 25
        font.pointSize: 16
        width: 300
        elide: Text.ElideRight
        text: parent.text
        Rectangle {
            border.color: "blue"
            color: "#110000FF"
            anchors.fill: parent
        }
    }

    Text {
        x: 25; y: 75
        width: 160
        font.pointSize: 16
        horizontalAlignment: Text.AlignRight
        text: "Largeur à 200 :"
    }
    Text {
        x: 200; y: 75
        font.pointSize: 16
        width: 200
        elide: Text.ElideRight
        text: parent.text
        Rectangle {
            border.color: "blue"
            color: "#110000FF"
            anchors.fill: parent
        }
    }

    Text {
        x: 25; y: 125
        width: 160
        font.pointSize: 16
        horizontalAlignment: Text.AlignRight
        text: "Largeur à 120 :"
    }
    Text {
        x: 200; y: 125
        font.pointSize: 16
        width: 120
        elide: Text.ElideRight
        text: parent.text
        Rectangle {
            border.color: "blue"
            color: "#110000FF"
            anchors.fill: parent
        }
    }

    Text {
        x: 25; y: 175
        width: 160
        font.pointSize: 16
        horizontalAlignment: Text.AlignRight
        text: "Largeur à 50 :"
    }
    Text {
        x: 200; y: 175
        font.pointSize: 16
        width: 50
        elide: Text.ElideRight
        text: parent.text
        Rectangle {
            border.color: "blue"
            color: "#110000FF"
            anchors.fill: parent
        }
    }
}
