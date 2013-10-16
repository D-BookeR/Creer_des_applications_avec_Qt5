import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    width: 300; height: 300
    GridLayout {
        anchors.fill: parent
        rows: 3; columns: 3
        Repeater {
            model: [
                Qt.AlignLeft | Qt.AlignTop,
                Qt.AlignLeft | Qt.AlignVCenter,
                Qt.AlignLeft | Qt.AlignBottom,
                Qt.AlignHCenter | Qt.AlignTop,
                Qt.AlignHCenter | Qt.AlignVCenter,
                Qt.AlignHCenter | Qt.AlignBottom,
                Qt.AlignRight | Qt.AlignTop,
                Qt.AlignRight | Qt.AlignVCenter,
                Qt.AlignRight | Qt.AlignBottom
            ]
            Rectangle {
                width: 50; height: 50
                color: "lightgreen"
                Layout.alignment: modelData
            }
        }
    }
    GridLayout {
        anchors.fill: parent
        rows: 3; columns: 3
        Repeater {
            model: 9
            Rectangle {
                border.color: "grey"
                color: "#000000ff"
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }
    }
}
