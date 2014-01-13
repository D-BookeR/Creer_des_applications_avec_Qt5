TEMPLATE = app

DEFINES += ENGINIO_SAMPLE_NAME=\\\"image-gallery\\\"

include(../../common/backendhelper/backendhelper.pri)

# for file dialogs we want widgets
QT += quick qml enginio widgets
SOURCES += ../main.cpp

mac: CONFIG -= app_bundle

OTHER_FILES += *.qml

RESOURCES += \
    gallery.qrc
