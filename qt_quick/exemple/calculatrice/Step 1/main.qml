import QtQuick 2.0

Rectangle {
    width: 248
    height: 368
    color: "black"

    Text {
        id: result
        color: "white"
        text: "Result"
        font.pointSize: 21
    }

    Grid {
        columns: 4
        spacing: 40
        anchors.top: result.bottom

        Button { text: "7" }
        Button { text: "8" }
        Button { text: "9" }
        Button { text: "+" }
        Button { text: "4" }
        Button { text: "5" }
        Button { text: "6" }
        Button { text: "–" }
        Button { text: "1" }
        Button { text: "2" }
        Button { text: "3" }
        Button { text: "×" }
        Button { text: "0" }
        Button { text: "." }
        Button { text: "=" }
        Button { text: "÷" }
    }
}
