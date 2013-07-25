import QtQuick 2.1
import QtQuick.Layouts 1.0
import "Calculator.js" as Calc

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
            text: Calc.evalToUser(computation) + " = " + result
            font.pointSize: 21
        }
    }

    Row {
        id: grid
        anchors.top: resultview.bottom
        anchors.topMargin: 20
        width: parent.width
        height: parent.height - anchors.topMargin - resultview.height
        focus: true

        GridLayout {
            id: keyboard

            height: parent.height
            width: 3/4 * parent.width

            columns: 3

            Button { text: "7" }
            Button { text: "8" }
            Button { text: "9" }
            Button { text: "4" }
            Button { text: "5" }
            Button { text: "6" }
            Button { text: "1" }
            Button { text: "2" }
            Button { text: "3" }
            Button { text: "0" }
            Button { text: "." }
            Button { text: "="; causeEvaluation: true }

            Keys.onReleased: {
                var text = "";

                switch(event.key) {
                }

                Calc.keyColour(text)
                event.accepted = true
            }
        }

        ColumnLayout {
            id: operations

            height: parent.height
            width: parent.width - keyboard.width

            Button { text: "+" }
            Button { text: "–"; evalText: "-" }
            Button { text: "×"; evalText: "*" }
            Button { text: "÷"; evalText: "/" }
            Button { text: "+" }
        }

        Keys.onReturnPressed: Calc.handleKey(true, "=", "grey")
        Keys.onEnterPressed: Calc.handleKey(true, "=", "grey")

        Keys.onUpPressed: {
            resultview.currentIndex -= 1
            if (resultview.currentIndex < 0)
                resultview.currentIndex = 0
        }
        Keys.onDownPressed: {
            resultview.currentIndex += 1
            if (resultview.currentIndex == resultview.count)
                resultview.currentIndex = resultview.count - 1
        }

        Keys.onPressed: {
            switch(event.key) {
            case Qt.Key_0:
            case Qt.Key_1:
            case Qt.Key_2:
            case Qt.Key_3:
            case Qt.Key_4:
            case Qt.Key_5:
            case Qt.Key_6:
            case Qt.Key_7:
            case Qt.Key_8:
            case Qt.Key_9:
            case Qt.Key_Period:
            case Qt.Key_Plus:
            case Qt.Key_Minus:
            case Qt.Key_Slash:
            case Qt.Key_Asterisk:
                Calc.handleKey(false, event.text, "grey")
                event.accepted = true
                break;
            }
        }

        Keys.onReleased: {
            var text = "";

            switch(event.key) {
            case Qt.Key_0:
            case Qt.Key_1:
            case Qt.Key_2:
            case Qt.Key_3:
            case Qt.Key_4:
            case Qt.Key_5:
            case Qt.Key_6:
            case Qt.Key_7:
            case Qt.Key_8:
            case Qt.Key_9:
            case Qt.Key_Period:
            case Qt.Key_Plus:
            case Qt.Key_Minus:
            case Qt.Key_Slash:
            case Qt.Key_Asterisk:
                text = event.text;
                break;
            case Qt.Key_Return:
            case Qt.Key_Enter:
                text = "=";
                break;
            }

            Calc.keyColour(text)
            event.accepted = true
        }
    }
}
