import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    id: applicationwindow
    width: 176
    height: 346
    title: "designer-01"

    Item {
        id: item
        x: 8
        y: 8
        width: 160
        height: 330
        anchors.top: parent.top
        anchors.topMargin: 8
        Label {
            id: label_voie
            x: 73
            width: 62
            text: "Voie N"
            clip: false
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            font.bold: false
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
            opacity: 1
            verticalAlignment: Text.AlignTop
        }

        Label {
            id: label_amplitude
            text: "Amplitude (dB)"
            anchors.top: label_voie.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        ProgressBar {
            id: progress_bar_amplitude
            height: 12
            anchors.top: label_amplitude.bottom
            anchors.topMargin: 8
            value: 0.4
            anchors.rightMargin: 0
            anchors.right: parent.right
            indeterminate: false
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box_sliders
            height: 100
            anchors.top: progress_bar_amplitude.bottom
            anchors.topMargin: 8
            Slider {
                id: slider__vertical_1
                x: -10
                y: 3
                width: 12
                orientation: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                value: 0.5
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.left: parent.left
            }

            Slider {
                id: slider__vertical_2
                x: 18
                y: 0
                width: 12
                orientation: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                value: 0.6
                anchors.bottomMargin: 0
                anchors.leftMargin: 18
                anchors.left: parent.left
            }

            Slider {
                id: slider__vertical_3
                x: 36
                y: 0
                width: 12
                orientation: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                value: 0.7
                anchors.bottomMargin: 0
                anchors.leftMargin: 36
                anchors.left: parent.left
            }

            Slider {
                id: slider__vertical_4
                x: 54
                y: 0
                width: 12
                orientation: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                value: 0.8
                anchors.bottomMargin: 0
                anchors.leftMargin: 54
                anchors.left: parent.left
            }

            Slider {
                id: slider__vertical_5
                x: 72
                y: 0
                width: 12
                orientation: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                value: 0.9
                anchors.bottomMargin: 0
                anchors.leftMargin: 72
                anchors.left: parent.left
            }

            Slider {
                id: slider__vertical_6
                x: 90
                y: 0
                width: 12
                orientation: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                value: 0.8
                anchors.bottomMargin: 0
                anchors.leftMargin: 90
                anchors.left: parent.left
            }

            Slider {
                id: slider__vertical_7
                x: 108
                y: 0
                width: 12
                orientation: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                value: 0.6
                anchors.bottomMargin: 0
                anchors.leftMargin: 108
                anchors.left: parent.left
            }

            Slider {
                id: slider__vertical_8
                x: 126
                y: 0
                width: 12
                orientation: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                value: 0.4
                anchors.bottomMargin: 0
                anchors.leftMargin: 126
                anchors.left: parent.left
            }
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        ComboBox {
            id: combo_box1
            anchors.top: label_preferences.bottom
            anchors.topMargin: 8
            activeFocusOnPress: false
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        Label {
            id: label_preferences
            x: 6
            text: "Préférences de l'égaliseur:"
            anchors.top: group_box_sliders.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box1
            height: 94
            anchors.top: combo_box1.bottom
            anchors.topMargin: 8
            RadioButton {
                id: radio_button1
                x: 0
                y: 0
                text: "16 bits"
                checked: true
            }

            RadioButton {
                id: radio_button2
                x: 0
                y: 26
                text: "20 bits"
            }

            RadioButton {
                id: radio_button3
                x: 0
                y: 52
                text: "24 bits"
                checked: false
            }
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            title: "Résolution"
            anchors.left: parent.left
        }
        anchors.leftMargin: 8
        anchors.left: parent.left
    }


}
