import QtQuick 2.0

Rectangle {
    width: 200
    height: 150
    Text {
        text: website
        anchors.centerIn: parent
        renderType: Text.NativeRendering
    }
}
