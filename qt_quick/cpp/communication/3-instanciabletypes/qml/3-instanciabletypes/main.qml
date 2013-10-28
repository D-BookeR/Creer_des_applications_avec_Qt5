import QtQuick 2.0
import MyLib 1.0

Rectangle {
    width: 250
    height: 250

    Human {
        id: paul
        name: "Paul";
        age: 26
        size: 192
    }

    SGRect {
        x: 25; y: 25
        width: 150; height: 150
        color: "lightblue"
    }

    PainterRect {
        x: 75; y: 75
        width: 150; height: 150
        color: "lightgreen"
    }
}
