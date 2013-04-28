import QtQuick 2.0

Rectangle {
    width: 700; height: 500

    Rectangle {
        width: 700; height: 300
        color: "lightblue"

        Rectangle {
            x: 100; y: 100
            width: 500; height: 400
            color: "salmon"
            opacity: 0.5

            Rectangle {
                x: 100; y: 100
                width: 100; height: 200
                color: "yellow"
            }

            Rectangle {
                x: 300; y: 100
                width: 100; height: 200
                color: "yellow"
                opacity: 0.5
            }
        }
    }
}

