import QtQuick 2.0

Rectangle {
    id: rect
    width: 100; height: 300
    Rectangle {
        id: redLight
        x: 10; y: 10
        width: 80; height: 80
        radius: 40
        color: "red"
    }
    Rectangle {
        id: orangeLight
        x: 10; y: 110
        width: 80; height: 80
        radius: 40
        color: "black"
    }
    Rectangle {
        id: greenLight
        x: 10; y: 210
        width: 80; height: 80
        radius: 40
        color: "black"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            switch (rect.state) {
            case "": rect.state = "orange"; break
            case "orange": rect.state = "green"; break
            default: rect.state = ""
            }
        }
    }

    states: [
        State {
            name: "orange"
            PropertyChanges { target: redLight; color: "black" }
            PropertyChanges { target: orangeLight; color: "orange" }
            PropertyChanges { target: greenLight; color: "black" }
        },
        State {
            name: "green"
            PropertyChanges { target: redLight; color: "black" }
            PropertyChanges { target: orangeLight; color: "black" }
            PropertyChanges { target: greenLight; color: "green" }
        }
    ]
}
