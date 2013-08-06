import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    id: applicationwindow1
    width: 1024
    height: 368
    title: "designer-01"

    Column {
        id: column1
        x: 8
        y: 8
        width: 160
        height: 352
        anchors.top: parent.top
        anchors.topMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        visible: true

        Label {
            id: label_voie
            x: 73
            width: 62
            text: "Voie 1"
            opacity: 1
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

    Column {
        id: column2
        x: 174
        y: 8
        width: 160
        height: 352
        anchors.top: parent.top
        anchors.topMargin: 8
        Label {
            id: label_voie1
            x: 73
            width: 62
            text: "Voie 2"
            clip: false
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            font.bold: false
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            opacity: 1
        }

        Label {
            id: label_amplitude1
            text: "Amplitude (dB)"
            anchors.top: label_voie1.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        ProgressBar {
            id: progress_bar_amplitude1
            height: 12
            anchors.top: label_amplitude1.bottom
            anchors.topMargin: 8
            value: 0.4
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            indeterminate: false
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box_sliders1
            height: 100
            anchors.top: progress_bar_amplitude1.bottom
            anchors.topMargin: 8
            Slider {
                id: slider__vertical_9
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
                id: slider__vertical_10
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
                id: slider__vertical_11
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
                id: slider__vertical_12
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
                id: slider__vertical_13
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
                id: slider__vertical_14
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
                id: slider__vertical_15
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
                id: slider__vertical_16
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
            id: combo_box2
            anchors.top: label_preferences1.bottom
            anchors.topMargin: 8
            activeFocusOnPress: false
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        Label {
            id: label_preferences1
            x: 6
            text: "Préférences de l'égaliseur:"
            anchors.top: group_box_sliders1.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box2
            height: 94
            anchors.top: combo_box2.bottom
            anchors.topMargin: 8
            RadioButton {
                id: radio_button4
                x: 0
                y: 0
                text: "16 bits"
                checked: true
            }

            RadioButton {
                id: radio_button5
                x: 0
                y: 26
                text: "20 bits"
            }

            RadioButton {
                id: radio_button6
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
        visible: true
        anchors.leftMargin: 176
        anchors.left: parent.left
    }

    Column {
        id: column3
        x: 340
        y: 8
        width: 160
        height: 352
        anchors.top: parent.top
        anchors.topMargin: 8
        Label {
            id: label_voie2
            x: 73
            width: 62
            text: "Voie 3"
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
            id: label_amplitude2
            text: "Amplitude (dB)"
            anchors.top: label_voie2.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        ProgressBar {
            id: progress_bar_amplitude2
            height: 12
            anchors.top: label_amplitude2.bottom
            anchors.topMargin: 8
            value: 0.4
            anchors.rightMargin: 0
            anchors.right: parent.right
            indeterminate: false
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box_sliders2
            height: 100
            anchors.top: progress_bar_amplitude2.bottom
            anchors.topMargin: 8
            Slider {
                id: slider__vertical_17
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
                id: slider__vertical_18
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
                id: slider__vertical_19
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
                id: slider__vertical_20
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
                id: slider__vertical_21
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
                id: slider__vertical_22
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
                id: slider__vertical_23
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
                id: slider__vertical_24
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
            id: combo_box3
            anchors.top: label_preferences2.bottom
            anchors.topMargin: 8
            activeFocusOnPress: false
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        Label {
            id: label_preferences2
            x: 6
            text: "Préférences de l'égaliseur:"
            anchors.top: group_box_sliders2.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box3
            height: 94
            anchors.top: combo_box3.bottom
            anchors.topMargin: 8
            RadioButton {
                id: radio_button7
                x: 0
                y: 0
                text: "16 bits"
                checked: true
            }

            RadioButton {
                id: radio_button8
                x: 0
                y: 26
                text: "20 bits"
            }

            RadioButton {
                id: radio_button9
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
        visible: true
        anchors.leftMargin: 344
        anchors.left: parent.left
    }

    Column {
        id: column4
        x: 506
        y: 8
        width: 160
        height: 352
        anchors.top: parent.top
        anchors.topMargin: 8
        Label {
            id: label_voie3
            x: 73
            width: 62
            text: "Voie 4"
            clip: false
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            font.bold: false
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            opacity: 1
        }

        Label {
            id: label_amplitude3
            text: "Amplitude (dB)"
            anchors.top: label_voie3.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        ProgressBar {
            id: progress_bar_amplitude3
            height: 12
            anchors.top: label_amplitude3.bottom
            anchors.topMargin: 8
            value: 0.4
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            indeterminate: false
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box_sliders3
            height: 100
            anchors.top: progress_bar_amplitude3.bottom
            anchors.topMargin: 8
            Slider {
                id: slider__vertical_25
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
                id: slider__vertical_26
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
                id: slider__vertical_27
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
                id: slider__vertical_28
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
                id: slider__vertical_29
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
                id: slider__vertical_30
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
                id: slider__vertical_31
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
                id: slider__vertical_32
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
            id: combo_box4
            anchors.top: label_preferences3.bottom
            anchors.topMargin: 8
            activeFocusOnPress: false
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        Label {
            id: label_preferences3
            x: 6
            text: "Préférences de l'égaliseur:"
            anchors.top: group_box_sliders3.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box4
            height: 94
            anchors.top: combo_box4.bottom
            anchors.topMargin: 8
            RadioButton {
                id: radio_button10
                x: 0
                y: 0
                text: "16 bits"
                checked: true
            }

            RadioButton {
                id: radio_button11
                x: 0
                y: 26
                text: "20 bits"
            }

            RadioButton {
                id: radio_button12
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
        visible: true
        anchors.leftMargin: 512
        anchors.left: parent.left
    }

    Column {
        id: column5
        x: 672
        y: 8
        width: 160
        height: 352
        anchors.top: parent.top
        anchors.topMargin: 8
        Label {
            id: label_voie4
            x: 73
            width: 62
            text: "Voie 5"
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
            id: label_amplitude4
            text: "Amplitude (dB)"
            anchors.top: label_voie4.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        ProgressBar {
            id: progress_bar_amplitude4
            height: 12
            anchors.top: label_amplitude4.bottom
            anchors.topMargin: 8
            value: 0.4
            anchors.rightMargin: 0
            anchors.right: parent.right
            indeterminate: false
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box_sliders4
            height: 100
            anchors.top: progress_bar_amplitude4.bottom
            anchors.topMargin: 8
            Slider {
                id: slider__vertical_33
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
                id: slider__vertical_34
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
                id: slider__vertical_35
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
                id: slider__vertical_36
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
                id: slider__vertical_37
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
                id: slider__vertical_38
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
                id: slider__vertical_39
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
                id: slider__vertical_40
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
            id: combo_box5
            anchors.top: label_preferences4.bottom
            anchors.topMargin: 8
            activeFocusOnPress: false
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        Label {
            id: label_preferences4
            x: 6
            text: "Préférences de l'égaliseur:"
            anchors.top: group_box_sliders4.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box5
            height: 94
            anchors.top: combo_box5.bottom
            anchors.topMargin: 8
            RadioButton {
                id: radio_button13
                x: 0
                y: 0
                text: "16 bits"
                checked: true
            }

            RadioButton {
                id: radio_button14
                x: 0
                y: 26
                text: "20 bits"
            }

            RadioButton {
                id: radio_button15
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
        visible: true
        anchors.leftMargin: 680
        anchors.left: parent.left
    }

    Column {
        id: column6
        x: 838
        y: 8
        width: 160
        height: 352
        anchors.top: parent.top
        anchors.topMargin: 8
        Label {
            id: label_voie5
            x: 73
            width: 62
            text: "Master"
            clip: false
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 0
            font.bold: false
            font.pointSize: 18
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            opacity: 1
        }

        Label {
            id: label_amplitude5
            text: "Amplitude (dB)"
            anchors.top: label_voie5.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        ProgressBar {
            id: progress_bar_amplitude5
            height: 12
            anchors.top: label_amplitude5.bottom
            anchors.topMargin: 8
            value: 0.4
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            indeterminate: false
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box_sliders5
            height: 100
            anchors.top: progress_bar_amplitude5.bottom
            anchors.topMargin: 8
            Slider {
                id: slider__vertical_41
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
                id: slider__vertical_42
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
                id: slider__vertical_43
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
                id: slider__vertical_44
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
                id: slider__vertical_45
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
                id: slider__vertical_46
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
                id: slider__vertical_47
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
                id: slider__vertical_48
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
            id: combo_box6
            anchors.top: label_preferences5.bottom
            anchors.topMargin: 8
            activeFocusOnPress: false
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        Label {
            id: label_preferences5
            x: 6
            text: "Préférences de l'égaliseur:"
            anchors.top: group_box_sliders5.bottom
            anchors.topMargin: 8
            anchors.leftMargin: 0
            anchors.left: parent.left
        }

        GroupBox {
            id: group_box6
            height: 94
            anchors.top: combo_box6.bottom
            anchors.topMargin: 8
            RadioButton {
                id: radio_button16
                x: 0
                y: 0
                text: "16 bits"
                checked: true
            }

            RadioButton {
                id: radio_button17
                x: 0
                y: 26
                text: "20 bits"
            }

            RadioButton {
                id: radio_button18
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
        visible: true
        anchors.leftMargin: 848
        anchors.left: parent.left
    }
    
}
