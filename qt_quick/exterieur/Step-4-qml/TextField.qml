import QtQuick 2.0

Rectangle {
    id: field
    width: 150; height: 26
    color: "white"; radius: 10
    border.color: input.focus ? "#C0C0FF" : "#545454"
    border.width: 1
    clip: true

    property string label: ""
    property alias text: input.text
    property alias input: input
    signal finished()

    Text {
        anchors {
            fill: parent
            leftMargin: 15
            rightMargin: 15
        }
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        renderType: TextInput.NativeRendering
        visible: !input.focus && input.text === ""
        color: "darkgray"
        text: field.label
    }

    TextInput {
        id: input
        anchors {
            fill: parent
            leftMargin: 15
            rightMargin: 15
        }
        color: "gray"
        font.bold: true
        horizontalAlignment: TextInput.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter
        renderType: TextInput.NativeRendering
        selectByMouse: true
        Keys.onPressed: {
            if (event.key === Qt.Key_Escape)
                input.focus = false;
            if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
                field.finished();
                input.focus = false;
            }
        }
    }
}
