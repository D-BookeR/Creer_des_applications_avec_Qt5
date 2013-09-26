import QtQuick 2.0

Column {
    height: 100
    spacing: 15

    Repeater {
        id: view
        anchors {
            left: parent.left
            right: parent.right
            leftMargin: 15
            rightMargin: 15
        }
        clip: true
        model: currentModel
        delegate: WeatherDelegate {
            anchors {
                left: view.left
                right: view.right
            }
            dateStr: "At " + time
            temperature: temp + " °C"
        }
    }

    Separator { }
}
