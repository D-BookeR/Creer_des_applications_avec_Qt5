import QtQuick 2.1

Grid {
    columns: 2; rows: 2
    spacing: 5

    Rectangle {
        id: topLeft
        width: 130; height: 40
        focus: true
        border.color: "grey"
        KeyNavigation.right: topRight
        KeyNavigation.down: bottomLeft
        Text {
            anchors.centerIn: parent
            text: parent.activeFocus ? "Est actif" : "N'est pas actif"
            color: parent.activeFocus ? "green" : "red"
            font.pointSize: 14
        }
    }

    Rectangle {
        id: topRight
        width: 130; height: 40
        border.color: "grey"
        KeyNavigation.left: topLeft
        KeyNavigation.down: bottomRight
        Text {
            anchors.centerIn: parent
            text: parent.activeFocus ? "Est actif" : "N'est pas actif"
            color: parent.activeFocus ? "green" : "red"
            font.pointSize: 14
        }
    }

    Rectangle {
        id: bottomLeft
        width: 130; height: 40
        border.color: "grey"
        KeyNavigation.right: bottomRight
        KeyNavigation.up: topLeft
        Text {
            anchors.centerIn: parent
            text: parent.activeFocus ? "Est actif" : "N'est pas actif"
            color: parent.activeFocus ? "green" : "red"
            font.pointSize: 14
        }
    }

    Rectangle {
        id: bottomRight
        width: 130; height: 40
        border.color: "grey"
        KeyNavigation.left: bottomLeft
        KeyNavigation.up: topRight
        Text {
            anchors.centerIn: parent
            text: parent.activeFocus ? "Est actif" : "N'est pas actif"
            color: parent.activeFocus ? "green" : "red"
            font.pointSize: 14
        }
    }
}
