import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    id: applicationwindow1
    width: 1056
    height: 346
    title: "designer-01"

    Row {
        id: row1
        anchors.fill: parent

        Channel {
            id: channel1
            channelName: "Voie 1"
            x: 0 ; y: 0
            anchors.verticalCenter: parent.verticalCenter
        }

        Channel {
            id: channel2
            channelName: "Voie 2"
            x: 176 ; y: 0
            anchors.verticalCenter: parent.verticalCenter
        }

        Channel {
            id: channel3
            channelName: "Voie 3"
            x: 176*2; y: 0
            anchors.verticalCenter: parent.verticalCenter
        }

        Channel {
            id: channel4
            channelName: "Voie 4"
            x: 176*3 ; y: 0
            anchors.verticalCenter: parent.verticalCenter
        }

        Channel {
            id: channel5
            channelName: "Voie 5"
            x: 176*4 ; y: 0
            anchors.verticalCenter: parent.verticalCenter
        }

        Channel {
            id: channel6
            channelName: "Master"
            x: 176*5 ; y: 0
            anchors.verticalCenter: parent.verticalCenter
        }
    }


}
