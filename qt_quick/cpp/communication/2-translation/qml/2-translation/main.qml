import QtQuick 2.0

Rectangle {
    width: 300
    height: 175

    Row {
        id: topBar
        height: 75
        spacing: 20
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
        }

        Button {
            text: qsTr("French") + tr.language
            anchors.verticalCenter: parent.verticalCenter
            onClicked: tr.setLanguage("fr");
        }

        Button {
            text: qsTr("English") + tr.language
            anchors.verticalCenter: parent.verticalCenter
            onClicked: tr.setLanguage("en");
        }
    }

    Separator {
        id: sep
        anchors {
            top: topBar.bottom
            topMargin: 10
        }
    }

    Item {
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: sep.bottom
        }

        Button {
            text: qsTr("Hello World !") + tr.language
            anchors.centerIn: parent
            enabled: false
        }
    }
}
