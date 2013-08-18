import QtQuick 2.0

Rectangle {
    width: 350; height: 50
    Component.onCompleted: timer.start()
    property int count: 0
    Timer {
        id: timer
        interval: 1000
        repeat: true
        onTriggered: count = count + 1
    }
    Text {
        anchors.centerIn: parent
        font.pointSize: 16
        text: "L'application a démarré depuis " + count + " s"
    }
}

