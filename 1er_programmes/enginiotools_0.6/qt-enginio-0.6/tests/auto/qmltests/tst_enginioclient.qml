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

    SignalSpy {
           id: finishedSpy
           target: enginio
           signalName: "finished"
    }

    SignalSpy {
           id: errorSpy
           target: enginio
           signalName: "error"
    }

    TestCase {
        name: "EnginioClient: ObjectOperation CRUD"

        function init() {
            finishedSpy.clear()
            errorSpy.clear()
        }

        function test_CRUD() {
            var finished = 0;
            var reply = enginio.create({ "objectType": AppConfig.testObjectType,
                                         "testCase" : "EnginioClient_ObjectOperation",
                                         "title" : "CREATE",
                                         "count" : 1337,
                                       }, Enginio.ObjectOperation);

            finishedSpy.wait()
            compare(finishedSpy.count, ++finished)
            compare(errorSpy.count, 0)

            var objectId = reply.data.id

            compare(reply.data.title, "CREATE")
            compare(reply.data.count, 1337)

            reply = enginio.query({ "objectType": AppConfig.testObjectType,
                                    "query" : { "id" : objectId }
                                  }, Enginio.ObjectOperation);

            finishedSpy.wait()
            compare(finishedSpy.count, ++finished)
            compare(errorSpy.count, 0)
            verify(reply.data.results !== undefined)
            compare(reply.data.results.length, 1)
            compare(reply.data.results[0].id, objectId)
            compare(reply.data.results[0].testCase, "EnginioClient_ObjectOperation")
            compare(reply.data.results[0].title, "CREATE")
            compare(reply.data.results[0].count, 1337)

            reply = enginio.update({ "objectType": AppConfig.testObjectType,
                                     "id" : objectId,
                                     "testCase" : "EnginioClient_ObjectOperation_Update",
                                     "title" : "UPDATE",
                                  }, Enginio.ObjectOperation);

            finishedSpy.wait()
            compare(finishedSpy.count, ++finished)
            compare(errorSpy.count, 0)
            compare(reply.data.id, objectId)
            compare(reply.data.testCase, "EnginioClient_ObjectOperation_Update")
            compare(reply.data.title, "UPDATE")
            compare(reply.data.count, 1337)

            reply = enginio.remove({ "objectType": AppConfig.testObjectType,
                                       "id" : objectId
                                   }, Enginio.ObjectOperation);

            finishedSpy.wait()
            compare(finishedSpy.count, ++finished)
            compare(errorSpy.count, 0)

            reply = enginio.query({ "objectType": AppConfig.testObjectType
                                  }, Enginio.ObjectOperation);

            finishedSpy.wait()
            compare(finishedSpy.count, ++finished)
            compare(errorSpy.count, 0)
            compare(reply.data.results.length, 0)
        }
    }
}
