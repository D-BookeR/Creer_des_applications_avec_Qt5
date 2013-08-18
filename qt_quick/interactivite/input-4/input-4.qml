import QtQuick 2.1

Rectangle {
    id: mainWindow
    width: 400; height: 150

    ToolBar {
        id: toolBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
    }

    TextEdit {
        id: editor
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolBar.bottom
        anchors.bottom: statusBar.top
        //focus: true
        font.pointSize: 14
        selectByMouse: true
        selectedTextColor: "yellow"
        selectionColor: "black"
        wrapMode: TextEdit.Wrap
        text: "un exemple de texte <b>avec</b> mise en forme."
        textMargin: 5
        textFormat: TextEdit.RichText
    }

    Rectangle {
        id: statusBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 25
        color: "lightgrey"
        Text {
            anchors.centerIn: parent
            font.pointSize: 12
            text: "Curseur : " + editor.cursorPosition + " - " +
                  "Sélection : " + editor.selectionStart + " à " + editor.selectionEnd
        }
    }
}
