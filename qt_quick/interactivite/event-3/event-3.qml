import QtQuick 2.0

Rectangle {
    width: 400; height: 150
    property int countWidth: 0
    property int countHeight: 0
    Text {
        anchors.centerIn: parent
        font.pointSize: 16
        text: "La largeur a été changée " + countWidth + " fois\n" +
              "et la hauteur a été changée " + countHeight + " fois"
    }
    onWidthChanged: countWidth = countWidth + 1
    onHeightChanged: countHeight = countHeight + 1
}

