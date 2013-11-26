TEMPLATE = app

DEFINES += ENGINIO_SAMPLE_NAME=\\\"todo\\\"

include(../../common/backendhelper/backendhelper.pri)

QT += quick qml enginio widgets
SOURCES += ../main.cpp

mac: CONFIG -= app_bundle

OTHER_FILES += todo.qml
RESOURCES += todo.qrc
