import QtQuick 2.0
import MyLib 2.0

// Utilisez import MyLib 1.0 pour avoir accès uniqument
// à la propriété cost de Element

Rectangle {
    width: 360
    height: 360

    Element {
        id: elem
        name: "Elem"
        cost: 12
        size: 4
    }

    Component.onCompleted: {
        console.log("Name: " + elem.getName());
        console.log("Cost: " + elem.getCost());
        console.log("Size: " + elem.getSize());
    }
}
