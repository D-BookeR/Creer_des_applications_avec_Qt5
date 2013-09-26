import QtQuick 2.0

Item {
    opacity: 0
    Behavior on opacity { NumberAnimation { duration: 200 } }

    Rectangle {
        anchors.fill: parent
        opacity: 0.7
        color: "black"
    }

    MouseArea {
        enabled: parent.opacity > 0
        anchors.fill: parent
        onClicked: {
            parent.opacity = 0;
        }
    }

    Repeater {
        id: view
        width: 250
        height: 200
        anchors.centerIn: parent
        clip: true
        model: errorModel
        delegate: Rectangle {
            anchors {
                left: view.left
                right: view.right
                top: view.top
            }
            height: column.height
            radius: 10
            border.color: "#424242"
            border.width: 1
            gradient: Gradient {
                GradientStop { position: 0; color: "#222222" }
                GradientStop { position: 0.8; color: "#111111" }
            }

            Column {
                id: column
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: 15
                height: titleArea.height + sep.height
                    + contentsArea.height + 4 * spacing
                spacing: 15

                Text {
                    id: titleArea
                    text: title
                    color: "white"
                    font.bold: true
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    renderType: Text.NativeRendering
                    elide: Text.ElideRight
                    width: parent.width
                }
                Separator { id: sep; offset: 0 }
                Text {
                    id: contentsArea
                    text: contents
                    width: parent.width
                    height: contentHeight
                    color: "gray"
                    font.bold: true
                    font.pixelSize: 12
                    wrapMode: Text.Wrap
                    renderType: Text.NativeRendering
                    textFormat: Text.PlainText
                }
            }
        }
    }
}
