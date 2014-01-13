# Enginio Qt Library Changelog
## 0.6.0
* Improved documentation
* Improved stability in many "edge cases"
* Examples within Enginio are not dependent on hard-coded backend anymore
* Clearer and more precise error messages
* Client library has been moved under the Qt-Project umbrella
* Groundwork laid for coming websocket support
* New binary installers for Windows, Mac and Linux
* Renamed EnginioAuthentication to EnginioBasicAuthentication (Qt API change)
* EnginioModel defined an enums with default roles (Qt API change)

## 0.5.0 (July 5th 2013)
* New more Qt-like API, based on QNetworkAccessManager design
* QJS and QJson based API
* New classes:
 - EnginioClient: main class for all direct queries
 - EnginioModel: model for simple data access and fast View & Delegate integration
 - EnginioReply: class that contains query data and network status
 - EnginioAuthentication: basic authentication
* New building process
 - Enginio client library is now a Qt add-on module
 - Separate code for qml plugin that doesn't have to be built if not needed
* New repository layout: tests and examples were moved to the same repository
* All operation classes were removed


## 0.4.0 (May 31st 2013)
New:
* UsergroupOperation added
* Usergroup members can now be fetched with query operation
* Get usergroups of logged in user from QML

Fixes:
* Handle removed and null properties correctly in EnginioJsonObject
* Use default flags with ObjectModel
* Internal ACL fixes

## 0.3.0 (May 7th 2013)
New:
* Usage simplified by building Enginio library as a proper Qt5 module. Now only configuration required is `QT += enginio`.
* QML FileOperation added
* Chunked file upload implemented

Fixes:
* Build issues on Mac
* Object given to ObjectOperation::create/read/update methods updated properly when operation is finished

## 0.2.1 (April 19th 2013)
Fixes:
* QML plugin is installed under <QML_INSTALL_DIR>/qml

## 0.2.0 (April 16th 2013)
New:
* QueryOperation now supports fulltext search
* AclOperation added for handling object permissions
* FileOperation added for uploading files to backend
* <Enginio/Enginio> header added

Fixes:
* Build and API documentation fixes
* Various smaller bug fixes

## 0.1.0 (March 15th 2013)
New:
* Initial release version of the client library

Fixes:
* None
