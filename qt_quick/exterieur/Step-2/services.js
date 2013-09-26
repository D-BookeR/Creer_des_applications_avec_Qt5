.pragma library

var baseUrl = "http://api.worldweatheronline.com/free/v1/";
var token = "remplacez ceci par votre clé";

var services = {
    "Weather": baseUrl + "weather.ashx",
    "Search": baseUrl + "search.ashx",
    "Marine": baseUrl + "marine.ashx",
    "TimeZone": baseUrl + "tz.ashx"
};
