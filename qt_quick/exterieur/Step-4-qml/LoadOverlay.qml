import QtQuick 2.0

Item {
    AnimatedImage {
        anchors.centerIn: parent
        visible: main.searching
        source: "loading.gif"
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: main.searching ? 0.6 : 0
        Behavior on opacity { NumberAnimation { duration: 200 } }
    }
}
