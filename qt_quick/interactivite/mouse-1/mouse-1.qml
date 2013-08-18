import QtQuick 2.0

Grid {
    Repeater {
        model: [ "ArrowCursor", "UpArrowCursor", "CrossCursor",
            "WaitCursor", "IBeamCursor", "SizeVerCursor",
            "SizeHorCursor", "SizeBDiagCursor", "SizeFDiagCursor",
            "SizeAllCursor", "BlanckCursor", "SplitVCursor",
            "SplitHCursor", "PointingHandCursor", "ForbiddenCursor",
            "WhatshisCursor", "BusyCursor", "OpenHandCursor",
            "ClosedHandCursor" ]
        delegate:
            Rectangle {
            width: 180; height: 40
            Text {
                anchors.centerIn: parent
                font.pointSize: 14
                text: modelData
            }
            MouseArea {
                anchors.fill: parent
                cursorShape: index
            }
        }
    }
}
