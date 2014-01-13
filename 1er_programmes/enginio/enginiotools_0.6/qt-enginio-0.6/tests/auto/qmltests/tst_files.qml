import QtQuick 2.0
import QtTest 1.0
import Enginio 1.0
import "config.js" as AppConfig


// NOTE this test will only work if the server has the right setup:
// objects.files needs to have fileAttachment set to be a ref to files.


Item {
    id: root

    Enginio {
        id: enginio
        backendId: AppConfig.backendData.id
        backendSecret: AppConfig.backendData.secret
        serviceUrl: AppConfig.backendData.serviceUrl

        onError: {
            console.log("\n\n### ERROR")
            console.log(reply.errorString)
            reply.dumpDebugInfo()
            console.log("\n###\n")
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
        name: "Files"

        function init() {
            finishedSpy.clear()
            errorSpy.clear()
        }

        function test_upload_download() {
            var finished = 0

            //! [upload-create-object]
            var fileObject = {
                "objectType": AppConfig.testObjectType,
                "title": "Example object with file attachment",
            }
            var reply = enginio.create(fileObject);
            //! [upload-create-object]

            finishedSpy.wait()
            compare(finishedSpy.count, ++finished)
            compare(errorSpy.count, 0)
            verify(reply.data.id.length > 0)

            var fileName = AppConfig.testSourcePath + "/../common/enginio.png";

            //! [upload]
            var objectId = reply.data.id
            var uploadData = {
                "file":{
                    "fileName":"test.png"
                },
                "targetFileProperty": {
                    "objectType": AppConfig.testObjectType,
                    "id": objectId,
                    "propertyName": "fileAttachment"
                },
            }
            var uploadReply = enginio.uploadFile(uploadData, fileName)
            //! [upload]

            finishedSpy.wait()
            compare(finishedSpy.count, ++finished)
            compare(errorSpy.count, 0)

            //! [download]
            var downloadData = {
                "id": uploadReply.data.id,
            }
            var downloadReply = enginio.downloadFile(downloadData)
            //! [download]

            finishedSpy.wait()
            compare(finishedSpy.count, ++finished)
            compare(errorSpy.count, 0)

            verify(downloadReply.data.expiringUrl.length > 0)
        }
    }
}
