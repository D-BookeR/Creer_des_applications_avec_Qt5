import QtQuick 2.0

Rectangle {
    property string defaultText: ""
    property alias text: input.text
    property int defaultEchoMode: TextInput.Normal

    width: 300; height: 75
    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        width: 290; height: 30
        border.color: input.focus ? "darkgrey" : "lightgrey"
        border.width: input.focus ? 2 : 1
        radius: 5
        TextInput {
            id: input
            width: 280; height: 25
            anchors.centerIn: parent
            font.pointSize: 14
            color: "grey"
            text: defaultText
            clip: true
            onFocusChanged: {
                if (focus && text == defaultText) {
                    text = ""
                    color = "black"
                    echoMode = defaultEchoMode
                } else if (!focus && text == "") {
                    text = defaultText
                    color = "grey"
                    echoMode = TextInput.Normal
                }
            }
        }
    }
}
