function recvError(descr, data) {
    errorModel.clear();
    var obj = {
        "title": String(descr),
        "contents": data === "" ? "Empty answer from the service." : data
    };
    errorModel.append(obj);
}

function recvCurrentWeather(data, model) {
    model.clear();
    var obj = {
        "time": data.observation_time,
        "temp": data.temp_C,
        "desc": data.weatherDesc[0].value,
        "icon": data.weatherIconUrl[0].value,
        "winddir": data.winddir16Point,
        "windspeed": data.windspeedKmph
    };
    model.append(obj);
}

function recvForecastWeather(data, model) {
    model.clear();
    for (var item in data) {
        var obj = {
            "date": data[item].date,
            "tempMin": data[item].tempMinC,
            "tempMax": data[item].tempMaxC,
            "desc": data[item].weatherDesc[0].value,
            "icon": data[item].weatherIconUrl[0].value,
            "winddir": data[item].winddir16Point,
            "windspeed": data[item].windspeedKmph
        };
        model.append(obj);
    }
}

function recvRequestWeather(data) {
    main.location = data.query;
}

function recvWeather(data) {
    main.error = !data.error && !data.data.error ? false : true;
    if (!data.error && !data.data.error) {
        recvCurrentWeather(data.data.current_condition[0], currentModel);
        recvForecastWeather(data.data.weather, forecastModel);
        recvRequestWeather(data.data.request[0]);
    } else if (!data.data.error) {
        recvError(data.descr, data.data);
    } else {
        recvError("API Error", data.data.error[0].msg);
    }
    main.searching = false;
}
