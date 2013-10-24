import QtQuick 2.0

Image {
    property int borderWidth: 0
    property bool borderVisible: internalRect.border.width > 0
    Rectangle {
        id: internalRect
        width: parent.width;
        height: parent.height;
        border.width: borderWidth < 5 ? borderWidth : 5
        border.color: "#FF0000FF"
        color: "#000000FF"
    }
}
