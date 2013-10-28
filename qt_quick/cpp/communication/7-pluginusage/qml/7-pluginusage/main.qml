import QtQuick 2.0
import Human 1.0

Rectangle {
    width: 320
    height: 170

    Row {
        spacing: 25
        anchors.centerIn: parent

        HumanRenderer {
            ref: Human {
                name: "Jean"
                hp: 57
            }
        }

        HumanRenderer {
            ref: Human {
                name: "Sarah"
                hp: 83
            }
        }
    }
}
