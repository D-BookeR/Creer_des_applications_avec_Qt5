.pragma library

function sendRequest(uri, parameters, handler) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState === req.DONE) {
            var data = null;
            try {
                if (req.responseText === "")
                    throw "Error : empty answer";
                data = JSON.parse(req.responseText);
            } catch (err) {
                data = {
                    "error": true,
                    "descr": err,
                    "data": req.responseText
                };
            }
            handler(data);
        }
    }
    var params = "";
    if (parameters) {
        params = "?";
        for (var param in parameters)
            params += param + "=" + parameters[param] + "&";
        params = params.substring(0, params.length - 1);
    }
    req.open("GET", uri + params, true);
    req.send();
}
