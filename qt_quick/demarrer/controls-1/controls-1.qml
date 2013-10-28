import QtQuick 2.1
import QtQuick.Controls 1.0

Item {
    Button {
       text: "Fermer"
       anchors.centerIn: parent
       onClicked: Qt.quit()
    }
}
