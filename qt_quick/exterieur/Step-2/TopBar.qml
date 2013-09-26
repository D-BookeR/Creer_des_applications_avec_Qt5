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

    Separator { }
}
