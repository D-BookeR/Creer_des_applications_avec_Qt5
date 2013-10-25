import QtQuick 2.0

Rectangle {
    width: 200; height: 100
    property int count: 0
    function incremente() { count = count + 1 }
    color: "lightgreen"
    Text {
        anchors.centerIn: parent
        font.pointSize: 16
        text: "Reçu " + parent.count + " signaux"
    }
}
