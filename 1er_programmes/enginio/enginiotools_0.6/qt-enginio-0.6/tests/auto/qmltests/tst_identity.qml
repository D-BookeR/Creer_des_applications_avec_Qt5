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

        onError: {
            console.log("\n\n### ERROR")
            console.log(reply.errorString)
            reply.dumpDebugInfo()
            console.log("\n###\n")
        }
    }

    EnginioBasicAuthentication {
        id: validIdentity
        user: "logintest"
        password: "logintest"
    }

    EnginioBasicAuthentication {
        id: invalidIdentity
        user: "INVALID"
        password: "INVALID"
    }

    SignalSpy {
        id: sessionAuthenticatedSpy
        target: enginio
        signalName: "sessionAuthenticated"
    }

    SignalSpy {
        id: sessionAuthenticationErrorSpy
        target: enginio
        signalName: "sessionAuthenticationError"
    }

    TestCase {
        name: "EnginioClient: Assign an identity"

        function init() {
            enginio.identity = null
            sessionAuthenticatedSpy.clear()
            sessionAuthenticationErrorSpy.clear()
        }

        function cleanupTestCase() {
            init()
        }

        function test_assignValidIdentity() {
            verify(enginio.authenticationState !== Enginio.Authenticated)
            enginio.identity = validIdentity
            sessionAuthenticatedSpy.wait()
            verify(enginio.authenticationState === Enginio.Authenticated)

            // reassign the same
            enginio.identity = null
            tryCompare(enginio, "authenticationState", Enginio.NotAuthenticated)
            enginio.identity = validIdentity
            sessionAuthenticatedSpy.wait()
            verify(enginio.authenticationState === Enginio.Authenticated)
        }

        function test_assignInvalidIdentity() {
            verify(enginio.authenticationState !== Enginio.Authenticated)
            enginio.identity = invalidIdentity
            sessionAuthenticationErrorSpy.wait()
            verify(enginio.authenticationState !== Enginio.Authenticated)
        }
    }
}
