import QtQuick 2.0

Row {
    id: form
    spacing: 15
    height: field.height

    property alias field: field
    property alias button: btn
    signal finished(string text);

    TextField {
        id: field
        anchors.verticalCenter: parent.verticalCenter
        onFinished: {
            input.focus = false;
            form.finished(text);
        }
    }

    Button {
        id: btn
        enabled: field.text !== ""
        anchors.verticalCenter: parent.verticalCenter
        onClicked: field.finished(field.text);
    }
}
