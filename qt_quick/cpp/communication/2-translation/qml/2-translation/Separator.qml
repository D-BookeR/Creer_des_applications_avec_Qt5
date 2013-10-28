import QtQuick 2.0

Rectangle {
    x: offset; height: 1
    width: parent.width - 2 * offset
    color: "lightblue"
    property int offset: 25
}
