import QtQuick 2.0

Column {
    id: topBar
    spacing: 15
    anchors {
        left: parent.left
        right: parent.right
        top: parent.top
        topMargin: 15
    }

    add: Transition { NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 200 } }
    property bool historyVisible: historyModel.count > 0 && form.field.input.focus
    signal finished(string text);

    Item {
        height: form.height
        anchors {
            left: parent.left
            right: parent.right
        }
        Text {
            anchors {
                left: parent.left
                right: form.left
                leftMargin: 25
                rightMargin: 25
                verticalCenter: parent.verticalCenter
            }
            text: main.location
            color: "white"
            elide: Text.ElideRight
            font.pixelSize: 14
            font.bold: true
            renderType: Text.NativeRendering
        }
        TextForm {
            id: form
            field.label: "City name..."
            button.text: "Search !"
            anchors {
                right: parent.right
                rightMargin: 15
            }
            onFinished: topBar.finished(text);
        }
    }

    Separator {
        visible: historyVisible
        text: "History"
    }

    Grid {
        id: grid
        visible: historyVisible
        height: Math.max(0, Math.ceil(historyModel.count / 2) * (60 + spacing) - spacing)
        anchors {
            left: parent.left
            right: parent.right
            leftMargin: 15
            rightMargin: 15
        }
        columns: 2
        spacing: 10
        Repeater {
            anchors.left: parent.left
            anchors.right: parent.right
            model: historyModel
            delegate: HistoryDelegate { }
        }
    }

    Separator { text: "Current weather" }

    function setCurrentSearch(text) {
        form.field.text = text;
    }
}
