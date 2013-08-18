import QtQuick 2.1

Column {
    spacing: 10
    Repeater {
        model: 5
        Rectangle {
            width: 130; height: 25
            Text {
                activeFocusOnTab: true
                anchors.centerIn: parent
                text: activeFocus ? "Est actif" : "N'est pas actif"
                color: activeFocus ? "green" : "red"
                font.pointSize: 14
                focus: true
                MouseArea {
                    anchors.fill: parent
                    onClicked: parent.focus = true
                }
            }
        }
    }
}
