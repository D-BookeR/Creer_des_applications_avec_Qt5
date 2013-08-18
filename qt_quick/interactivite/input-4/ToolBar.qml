import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

Rectangle {
    height: 80
    color: "lightgrey"
    Flow {
        anchors.fill: parent
        Rectangle {
            width: 80; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Text {
                anchors.centerIn: parent
                text: "Select"
                font.pointSize: 14
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: editor.selectAll()
            }
        }

        Rectangle {
            width: 80; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Text {
                anchors.centerIn: parent
                text: "Deselect"
                font.pointSize: 14
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: editor.deselect()
            }
        }

        Rectangle {
            width: 40; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Image {
                source: "images/Gnome-edit-cut.svg"
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: editor.cut()
            }
        }

        Rectangle {
            width: 40; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Image {
                source: "images/Gnome-edit-copy.svg"
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: editor.copy()
            }
        }

        Rectangle {
            width: 40; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Image {
                source: "images/Gnome-edit-paste.svg"
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: editor.paste()
            }
        }

        Rectangle {
            width: 60; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Text {
                anchors.centerIn: parent
                text: "Undo"
                font.pointSize: 14
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: editor.undo()
            }
        }

        Rectangle {
            width: 60; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Text {
                anchors.centerIn: parent
                text: "Redo"
                font.pointSize: 14
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: editor.redo()
            }
        }

        Rectangle {
            width: 40; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Image {
                source: "images/Gnome-format-text-bold.svg"
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: {
                    var start = editor.selectionStart
                    var end = editor.selectionEnd

                    var str = "<b>" + editor.getText(start, end) + "</b>"
                    editor.remove(start, end)
                    editor.insert(editor.selectionStart, str)
                }
            }
        }

        Rectangle {
            width: 40; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Image {
                source: "images/Gnome-format-text-italic.svg"
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: {
                    var start = editor.selectionStart
                    var end = editor.selectionEnd

                    var str = "<i>" + editor.getText(start, end) + "</i>"
                    editor.remove(start, end)
                    editor.insert(editor.selectionStart, str)
                }
            }
        }

        Rectangle {
            width: 40; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Image {
                source: "images/Gnome-format-text-underline.svg"
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: {
                    var start = editor.selectionStart
                    var end = editor.selectionEnd

                    var str = "<u>" + editor.getText(start, end) + "</u>"
                    editor.remove(start, end)
                    editor.insert(editor.selectionStart, str)
                }
            }
        }

        Rectangle {
            width: 40; height: 40
            radius: 5
            color: "lightgrey"
            border.color: "darkgrey"
            Image {
                source: "images/Gnome-format-text-strikethrough.svg"
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                onPressed: parent.color = "darkgrey"
                onReleased: parent.color = "lightgrey"
                onClicked: {
                    var start = editor.selectionStart
                    var end = editor.selectionEnd

                    var str = "<s>" + editor.getText(start, end) + "</s>"
                    editor.remove(start, end)
                    editor.insert(editor.selectionStart, str)
                }
            }
        }
    }
}
