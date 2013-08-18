import QtQuick 2.0

Rectangle {
    width: 350; height: 100
    property int count1: 0
    property int count2: 0
    Text {
        font.pointSize: 16
        anchors.centerIn: parent
        text: "Il y a eu " + count1 + " clics sur <a href='lien1'>ce premier lien</a><br>" +
              " et " + count2 + " clics sur <a href='lien2'>ce second lien</a>."
        onLinkActivated: {
            if (link == "lien1") count1 = count1 + 1
            else if (link == "lien2") count2 = count2 + 1
        }
    }
}

