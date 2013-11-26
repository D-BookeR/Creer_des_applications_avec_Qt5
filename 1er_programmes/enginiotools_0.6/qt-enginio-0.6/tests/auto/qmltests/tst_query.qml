import QtQuick 2.0
import QtTest 1.0
import Enginio 1.0
import "config.js" as AppConfig

Item {
    id: root

    Enginio {
        id: enginio
        backendId: AppConfig.backendData.id
        backendSecret: AppConfig.backendData.secret
        serviceUrl: AppConfig.backendData.serviceUrl

        property int errorCount: 0
        property int finishedCount: 0

        onError: {
            finishedCount += 1
            errorCount += 1
            console.log("\n\n### ERROR")
            console.log(reply.errorString)
            reply.dumpDebugInfo()
            console.log("\n###\n")
        }

        onFinished: {
            finishedCount += 1
        }
    }

    TestCase {
        name: "EnginioClient: ObjectOperation Query"

        function init() {
            enginio.errorCount = 0
            enginio.finishedCount = 0
        }

        function test_query() {
            var iterations = 50
            var reply

            for (var i = 0; i < iterations; ++i)
            {
                enginio.create({ "objectType": AppConfig.testObjectType,
                                   "testCase" : "EnginioClient_ObjectOperation",
                                   "title" : "test_Query_" + i,
                                   "count" : i,
                               }, Enginio.ObjectOperation);
            }

            var request = [0, 5, 25, 20, 50]
            var expected = [25, 20, 5, 0]

            tryCompare(enginio, "finishedCount", iterations, 25000)
            compare(enginio.errorCount, 0)
            enginio.finishedCount = 0

            reply = enginio.query({ "objectType": AppConfig.testObjectType,
                                    "query": { "count" : {  "$in": request } },
                                    "sort": [{"sortBy": "count", "direction": "desc"}]
                                  }, Enginio.ObjectOperation);

            tryCompare(enginio, "finishedCount", 1)
            compare(enginio.errorCount, 0)
            verify(reply.data.results !== undefined)

            var actualCount = reply.data.results.length
            compare(actualCount, expected.length)

            for (var i = 0; i < actualCount; ++i)
            {
                compare(reply.data.results[i].count, expected[i])
            }
        }
    }
}
