import QtQuick 2.0

Item {
    property alias text: textItem.text
    property string evalText: text
    property bool causeEvaluation: false

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
        onClicked: {
            if(! causeEvaluation) {
                main.computation += evalText
            } else if(main.computation.length > 0) {
                model.append({
                                 computation: main.computation,
                                 result: eval(main.computation)
                             })
                main.computation = ""
                resultview.currentIndex = model.count - 1
            }
        }
    }
}
