import QtQuick 2.0
import QtQuick.Layouts 1.0
import "Calculator.js" as Calc

Item {
    property alias text: textItem.text
    property string textColour: "white"
    property string evalText: text
    property bool causeEvaluation: false

    function colourDefault() {
        textColour = "white"
    }

    width: 30
    height: 50

    Layout.alignment: Qt.AlignVCenter | Qt.AlignCenter

    Text {
        id: textItem
        font.pixelSize: 48
        lineHeight: 0.75
        color: textColour != "white" ? textColour : (mouse.pressed ? "orange" : "white")
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: Calc.handleKey(causeEvaluation, evalText)
    }
}
