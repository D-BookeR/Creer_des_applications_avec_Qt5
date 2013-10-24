import QtQuick 2.0

Rectangle {
    width: 200; height: 100
    Component {
        id: repeaterDelegate
        Rectangle {
            x: xx; y: yy
            width: 10; height: 10
            radius: 5
            color: "red"
        }
    }
    ListModel {
        id: repeaterModel
    }
    Repeater {
        model: repeaterModel
        delegate: repeaterDelegate
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            onClicked: repeaterModel.append( { xx: Math.random()*width, yy: Math.random()*height } )
        }
    }
}
