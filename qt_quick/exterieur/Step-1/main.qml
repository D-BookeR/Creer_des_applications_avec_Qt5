import QtQuick 2.0
import "send.js" as Srv

Rectangle {
    width: 360
    height: 360
    Component.onCompleted: {
        Srv.reqWeather("Paris", 3);
    }
}
