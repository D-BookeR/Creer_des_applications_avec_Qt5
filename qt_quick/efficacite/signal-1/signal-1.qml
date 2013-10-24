import QtQuick 2.0

Rectangle {
    width: 680; height: 260
    Grid {
        y: 20
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20
        columns: 3
        Button {
            text: "Connecter"
            onSend: {
                sender.send.connect(rect1.incremente)
                sender.send.connect(rect2.incremente)
                sender.send.connect(rect3.incremente)
            }
        }
        Button {
            text: "Déconnecter"
            onSend: {
                sender.send.disconnect(rect1.incremente)
                sender.send.disconnect(rect2.incremente)
                sender.send.disconnect(rect3.incremente)
            }
        }
        Button {
            id: sender
            text: "Envoyer"
        }

        ReceiverRectangle { id: rect1 }
        ReceiverRectangle { id: rect2 }
        ReceiverRectangle { id: rect3 }

    }
}
