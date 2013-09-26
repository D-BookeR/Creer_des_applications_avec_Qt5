.import QtQuick.LocalStorage 2.0 as Sql

var appInfos = {
    "name": "WeatherApp",
    "version": "1.0",
    "descr": "A common weather application",
    "size": 1 * 1024 * 1024
};

function createDatabase(db) {
    db.transaction(function(db) {
        db.executeSql("CREATE TABLE IF NOT EXISTS History ( \
            date NUMERIC, \
            city TEXT UNIQUE, \
            days INTEGER);");
        });
}

function loadWeatherHistory() {
    historyModel.clear();
    var db = Sql.LocalStorage.openDatabaseSync(appInfos["name"],
        appInfos["version"], appInfos["descr"], appInfos["size"],
        createDatabase);
    db.readTransaction(function(db) {
        var res = db.executeSql("SELECT date, city FROM History ORDER BY date DESC LIMIT 6;");
        for (var i = 0; i < res.rows.length; ++i) {
            var item = res.rows.item(i);
            historyModel.append(item);
        }
    });
}

function logWeatherRequest(city, days) {
    var db = Sql.LocalStorage.openDatabaseSync(appInfos["name"],
        appInfos["version"], appInfos["descr"], appInfos["size"],
        createDatabase);
    db.transaction(function(db) {
        db.executeSql("INSERT OR REPLACE INTO History \
            VALUES(DATETIME('now'), ?, ?);", [city, days]);
    });
    loadWeatherHistory();
}
