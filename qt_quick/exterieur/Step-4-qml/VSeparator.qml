import QtQuick 2.0

Rectangle {
    color: "gray"
    height: parent.height - offset
    width: 1; x: offset / 2

    property int offset: 25
}
