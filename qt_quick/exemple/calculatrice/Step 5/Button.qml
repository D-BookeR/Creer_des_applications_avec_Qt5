import QtQuick 2.0
import "Calculator.js" as Calc

Item {
    property alias text: textItem.text
    property alias textColour: textItem.color
    property string evalText: text
    property bool causeEvaluation: false

    function colourDefault() {
        textItem.color = mouse.pressed ? "orange" : "white"
    }

    width: 30
    height: 50

    Text {
        id: textItem
        font.pixelSize: 48
        lineHeight: 0.75
        color: mouse.pressed ? "orange" : "white"
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: Calc.handleKey(causeEvaluation, evalText)
    }
}
