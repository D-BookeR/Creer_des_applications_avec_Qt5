import QtQuick 2.1
import QtQuick.Controls 1.0

Column {
    x: 10; y: 10
    width: 230; height: 585
    spacing: 10

    Button { width: 150; text: "Un bouton" }
    CheckBox { width: 150; text: "Un case à cocher" }
    RadioButton { width: 150; text: "Un bouton radio" }
    ComboBox { width: 150; model: [ "Une liste de choix", "Autre choix" ] }

    GroupBox {
        title: "Plusieurs cases à cocher"
        width: 150
        Column {
            spacing: 2
            CheckBox { text: "Choix 1" }
            CheckBox { text: "Choix 2" }
        }
    }
    GroupBox {
        title: "Plusieurs boutons radios"
        width: 150
        Column {
            ExclusiveGroup { id: group }
            RadioButton {
                text: "Choix 1"
                exclusiveGroup: group
                checked: true
            }
            RadioButton {
                text: "Choix 2"
                exclusiveGroup: group
            }
        }
    }

    Slider {
        id: slider
        minimumValue: 0
        maximumValue: 100
        value: 50
    }
    ProgressBar {
        minimumValue: 0
        maximumValue: 100
        value: slider.value
    }
    SpinBox {
        x: 50
        width: 100
        minimumValue: 0
        maximumValue: 1000
        value: 42
    }

    Label {
        text: "Un texte non modifiable"
        font.pixelSize: 18
        font.italic: true
        color: "steelblue"
    }
    TextArea { width: 200; text: "Un texte sur plusieurs lignes,\nmodifiable" }
    TextField { width: 200; text: "Un texte sur une ligne, modifiable" }
}

