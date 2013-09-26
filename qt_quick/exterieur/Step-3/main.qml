import QtQuick 2.0
import "send.js" as Srv
import "logs.js" as Logs

Rectangle {
    id: main
    width: 450; height: 715
    enabled: !searching
    color: "black"

    property bool error: false
    property bool searching: false
    property string location: "Paris"

    onErrorChanged: {
        if (error) {
            errorOverlay.opacity = 1;
            error = false;
        }
    }

    ListModel { id: currentModel }
    ListModel { id: forecastModel }
    ListModel { id: historyModel }
    ListModel { id: errorModel }

    MouseArea {
        anchors.fill: parent
        onClicked: main.focus = true;
    }

    TopBar {
        id: topBar
        onFinished: runWeatherRequest(text, 7);
    }

    CurrentView {
        id: currentView
        anchors {
            left: parent.left
            right: parent.right
            top: topBar.bottom
            topMargin: 15
        }
    }

    ForecastView {
        id: forecastView
        anchors {
            left: parent.left
            right: parent.right
            top: currentView.bottom
            bottom: parent.bottom
            topMargin: 20
        }
    }

    ErrorOverlay {
        id: errorOverlay
        anchors.fill: parent
    }

    LoadOverlay {
        id: loadOverlay
        anchors.fill: parent
    }

    function runWeatherRequest(city, days) {
        Srv.reqWeather(city, 7);
    }

    function logWeatherRequest(city, days) {
        Logs.logWeatherRequest(city, days);
    }

    Component.onCompleted: {
        Logs.loadWeatherHistory();
        var city = historyModel.count > 0 ? historyModel.get(0).city : location;
        runWeatherRequest(city, 7);
    }
}
