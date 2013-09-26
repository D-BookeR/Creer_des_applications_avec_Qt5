.import SQLExt 1.0 as Sql

var appInfos = {
    "host": "127.0.0.1",
    "name": "weatherapp",
    "user": "username",
    "pass": "password"
};

function createDatabase(db) {
    db.executeSql("CREATE TABLE IF NOT EXISTS History ( \
        date DATETIME, \
        city VARCHAR(100) UNIQUE, \
        days INTEGER);");
}

function loadWeatherHistory() {
    historyModel.clear();
    var db = Sql.SQLExt.openDatabaseSync(appInfos["host"],
        appInfos["name"], appInfos["user"], appInfos["pass"]);
    if (db.isOpen()) {
        createDatabase(db);
        var res = db.executeSql("SELECT date, city FROM History ORDER BY date DESC LIMIT 6;");
        for (var i = 0; !res.error && i < res.length; ++i) {
            var item = res.items[i];
            historyModel.append(item);
        }
    }
    Sql.SQLExt.freeDatabaseSync(db);
}

function logWeatherRequest(city, days) {
    var db = Sql.SQLExt.openDatabaseSync(appInfos["host"],
        appInfos["name"], appInfos["user"], appInfos["pass"]);
    if (db.isOpen()) {
        createDatabase(db);
        db.executeSql("REPLACE INTO History(date, city, days) VALUES(NOW(), '" + city + "', '" + days + "');");
    }
    Sql.SQLExt.freeDatabaseSync(db);
    loadWeatherHistory();
}
