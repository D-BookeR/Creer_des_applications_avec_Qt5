import QtQuick 2.0
import MyLib 1.0

Rectangle {
    width: 220
    height: 220

    property size mapSize: Qt.size(5, 5)
    property size caseSize: Qt.size(34, 34)

    Grid {
        anchors.centerIn: parent
        rows: mapSize.width
        columns: mapSize.height
        Repeater {
            id: yRepeater
            model: mapSize.height
            delegate: Repeater {
                model: mapSize.width
                delegate: Case {
                    width: caseSize.width
                    height: caseSize.height
                    infos: Ground { }
                }
            }
        }
    }

    function getCase(pos)
    {
        if (pos.x < 0 || mapSize.width <= pos.x
            || pos.y < 0 || mapSize.height <= pos.y)
            return null;

        var item = yRepeater.itemAt(pos.y);
        if (item !== null)
            return item.itemAt(pos.x);

        return null;
    }

    Component.onCompleted: {
        var woman = Builder.createHuman();
        woman.gender = Gender.Female;
        woman.position = Qt.point(1, 2);
        var tmp = getCase(Qt.point(1, 2));
        tmp.infos.unit = woman;
    }
}
