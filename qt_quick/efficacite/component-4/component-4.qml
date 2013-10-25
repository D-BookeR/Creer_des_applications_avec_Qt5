import QtQuick 2.0

Rectangle {
    width: 300; height: 200
    CounterButton {
        anchors.centerIn: parent
        onIncremented: label.text = "Il y a eu " + count + " clic" + (count == 1 ? "" : "s")
    }
    Text {
        id: label
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 16
        text: "Aucun clic"
    }
}

