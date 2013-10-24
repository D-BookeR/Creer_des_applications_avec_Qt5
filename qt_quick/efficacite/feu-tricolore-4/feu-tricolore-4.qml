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
            name: "off"
            PropertyChanges { target: redLight; color: "orange" }
            PropertyChanges { target: orangeLight; color: "orange" }
            PropertyChanges { target: greenLight; color: "orange" }
        },
        State {
            name: "on"
            PropertyChanges { target: redLight; color: "black" }
            PropertyChanges { target: orangeLight; color: "black" }
            PropertyChanges { target: greenLight; color: "black" }
        },
        State {
            name: "red"; extend: "on"
            PropertyChanges { target: redLight; color: "red" }
        },
        State {
            name: "orange"; extend: "on"
            PropertyChanges { target: orangeLight; color: "orange" }
        },
        State {
            name: "green"; extend: "on"
            PropertyChanges { target: greenLight; color: "green" }
        }
    ]
    state: "off"
    MouseArea {
        anchors.fill: parent
        onClicked: {
            switch (rect.state) {
            case "off": rect.state = "red"; break
            case "red": rect.state = "orange"; break
            case "orange": rect.state = "green"; break
            case "green": rect.state = "red"; break
            }
        }
    }
}
