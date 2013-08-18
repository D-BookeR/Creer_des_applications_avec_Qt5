import QtQuick 2.0

Column {
    z: 1
    Repeater {
        model: [ "red", "green", "blue" ]
        delegate:
            Button { color: modelData }
    }
}
