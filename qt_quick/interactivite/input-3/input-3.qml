import QtQuick 2.0

Rectangle {
    width: 300; height: 100
    TextInput {
        id: input
        anchors.centerIn: parent
        font.pointSize: 16
        focus: true
        validator: DoubleValidator { bottom: -10000; top: 10 }
    }
    Text {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 16
        text: input.acceptableInput ? "Le nombre est valide" : "Le nombre n'est pas valide"
        color: input.acceptableInput ? "green" : "red"
    }
}
