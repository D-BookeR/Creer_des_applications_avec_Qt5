import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    id: channel
    property string channelName: "Voie N"
    width: 176
    height: 346
    Item {
        id: item
        x: 8
        y: 8
        width: 160
        height: 330
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8

        Label {
            id: label_voie
            text: channelName
            x: 73
            width: 62
            clip: false
            font.bold: false
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
        }

        Label {
            id: label_amplitude
            text: "Amplitude (dB)"
            anchors.top: label_voie.bottom
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        ProgressBar {
            id: progress_bar_amplitude
            height: 12
            anchors.top: label_amplitude.bottom
            anchors.topMargin: 8
            indeterminate: false
            value: 0.4
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        GroupBox {
            id: group_box_sliders
            height: 100
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: progress_bar_amplitude.bottom
            anchors.topMargin: 8

            Slider {
                id: slider__vertical_1
                x: -10
                y: 3
                width: 12
                value: 0.5
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                orientation: 0
        }

        Slider {
            id: slider__vertical_2
            x: 18
            y: 0
            width: 12
            value: 0.6
            orientation: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.leftMargin: 18
            anchors.left: parent.left
        }

        Slider {
            id: slider__vertical_3
            x: 36
            y: 0
            width: 12
            value: 0.7
            orientation: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.leftMargin: 36
            anchors.left: parent.left
        }

        Slider {
            id: slider__vertical_4
            x: 54
            y: 0
            width: 12
            value: 0.8
            orientation: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.leftMargin: 54
            anchors.left: parent.left
        }

        Slider {
            id: slider__vertical_5
            x: 72
            y: 0
            width: 12
            value: 0.9
            orientation: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.leftMargin: 72
            anchors.left: parent.left
        }

        Slider {
            id: slider__vertical_6
            x: 90
            y: 0
            width: 12
            value: 0.8
            orientation: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.leftMargin: 90
            anchors.left: parent.left
        }

        Slider {
            id: slider__vertical_7
            x: 108
            y: 0
            width: 12
            value: 0.6
            orientation: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.leftMargin: 108
            anchors.left: parent.left
        }

        Slider {
            id: slider__vertical_8
            x: 126
            y: 0
            width: 12
            value: 0.4
            orientation: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.leftMargin: 126
            anchors.left: parent.left
        }
        }

        ComboBox {
            id: combo_box1
            activeFocusOnPress: false
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: label_preferences.bottom
            anchors.topMargin: 8
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
            title: "Résolution"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
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
        }
    }

    CheckBox {
        id: check_box
        x: 8 ; y: 6 ; width: 160; height: 39; text: ""
        checked: true
        onClicked: channel.state = check_box.checked ? '' : 'Invisible'
        visible: channelName != "Master"
    }

    ProgressBar {
        id: progress_bar_amplitude_vertical
        x: 0
        width: 12
        opacity: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        orientation: 0
        anchors.top: parent.top
        anchors.topMargin: 28
        value: 0.4
        indeterminate: false
        anchors.leftMargin: 8
        anchors.left: parent.left
    }

    states: [
        State {
            name: "Invisible"
            PropertyChanges {
                target: item
                opacity: 0
            }
            PropertyChanges {
                target: channel
                width: 23
            }

            PropertyChanges {
                target: progress_bar_amplitude_vertical
                opacity: 1
            }
        }
    ]

    transitions: [
        Transition {
            from: "*" ; to: "Invisible"
            SequentialAnimation {
                PropertyAnimation {
                    target: item
                    properties: "opacity";
                    duration: 100
                }
                NumberAnimation {
                    target: channel
                    properties: "width"
                    easing.type: Easing.OutCubic
                    duration: 300
                }
                PropertyAnimation {
                    target: progress_bar_amplitude_vertical
                    properties: "opacity";
                    duration: 200
                }
            }
        },

        Transition {
            from: "Invisible" ; to: "*"
            SequentialAnimation {
                PropertyAnimation {
                    target: progress_bar_amplitude_vertical
                    properties: "opacity";
                    duration: 100
                }
                NumberAnimation {
                    target: channel
                    properties: "width"
                    easing.type: Easing.InCubic
                    duration: 400
                }
                PropertyAnimation {
                    target: item
                    properties: "opacity";
                    duration: 200
                }
            }
        }
    ]
}
