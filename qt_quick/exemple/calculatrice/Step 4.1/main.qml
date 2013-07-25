import QtQuick 2.0

Rectangle {
    id: main

    width: 248
    height: 460
    color: "black"

    property string computation

    ListView {
        id: resultview
        width: parent.width
        height: 100
        model: ListModel { id: model }
        clip: true

        highlight: Rectangle {
            color: "darkred"
            radius: 5
            width: resultview.currentItem.width
        }

        delegate: Text {
            color: "white"
            text: computation + " = " + result
            font.pointSize: 21
        }
    }

    Grid {
        id: grid
        columns: 4
        spacing: 40
        anchors.top: resultview.bottom
        anchors.topMargin: 20

        Button { text: "7" }
        Button { text: "8" }
        Button { text: "9" }
        Button { text: "+" }
        Button { text: "4" }
        Button { text: "5" }
        Button { text: "6" }
        Button { text: "–"; evalText: "-" }
        Button { text: "1" }
        Button { text: "2" }
        Button { text: "3" }
        Button { text: "×"; evalText: "*" }
        Button { text: "0" }
        Button { text: "." }
        Button { text: "="; causeEvaluation: true }
        Button { text: "÷"; evalText: "/" }
    }
}
