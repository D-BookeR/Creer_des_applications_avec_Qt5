import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

Item {
    Button {
        text: "Fermer"
        anchors.centerIn: parent
        onClicked: Qt.quit()
        
        style: ButtonStyle {
            background: Rectangle {
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#fff" }
                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#bbb" }
                }
            }
        }
    }
}
