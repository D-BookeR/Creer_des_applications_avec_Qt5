import QtQuick 2.0
import MyLib 1.0

Item {
    property QtObject infos

    Item {
        width: 10
        height: 10
        anchors {
            left: parent.left
            top: parent.top
            leftMargin: 1
            topMargin: 1
        }

        Image {
            source: infos ? infos.resource : ""
            anchors.fill: parent
        }
    }

    Image {
        source: infos && infos.unit ? infos.unit.resource : ""
        anchors.verticalCenterOffset: 4
        anchors.centerIn: parent
    }

    Rectangle {
        color: "transparent"
        anchors.fill: parent
        anchors.topMargin: 1
        anchors.rightMargin: 1
        border.width: 1
        border.color: "darkgray"
    }
}
