import QtQuick 2.0

ListView {
    id: view
    spacing: 15
    anchors {
        left: parent.left
        right: parent.right
        leftMargin: 15
        rightMargin: 15
    }
    clip: true
    model: forecastModel
    delegate: WeatherDelegate {
        anchors {
            left: contentItem.left
            right: contentItem.right
        }
        dateStr: "The " + date
        temperature: "From " + tempMin + " to " + tempMax + " °C"
    }
}
