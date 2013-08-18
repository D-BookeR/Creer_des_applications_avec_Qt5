import QtQuick 2.0

TextInput {
    anchors.centerIn: parent
    font.pointSize: 14
    text: "Un texte particulièrement long. Beaucoup trop long !"
    clip: true
    Rectangle {
        anchors.fill: parent
        color: "lightsalmon"
        z: -1
    }
}
