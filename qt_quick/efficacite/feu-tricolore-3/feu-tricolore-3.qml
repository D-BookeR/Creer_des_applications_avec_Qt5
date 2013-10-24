import QtQuick 2.0

Rectangle {
    id: rect
    width: 100; height: 300
    Rectangle {
        id: redLight
        x: 10; y: 10
        width: 80; height: 80
        radius: 40
        color: "black"
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

    states: [
        State {
            name: "red"
            PropertyChanges { target: redLight; color: "red" }
        },
        State {
            name: "orange"
            PropertyChanges { target: orangeLight; color: "orange" }
        },
        State {
            name: "green"
            PropertyChanges { target: greenLight; color: "green" }
        }
    ]
    state: "red"
    MouseArea {
        anchors.fill: parent
        onClicked: {
            switch (rect.state) {
            case "red": rect.state = "orange"; break
            case "orange": rect.state = "green"; break
            case "green": rect.state = "red"; break
            }
        }
    }
}
