folder_01.source = qml/2-translation
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01
QML_IMPORT_PATH =


SOURCES += main.cpp translation.cpp
HEADERS += translation.h
TRANSLATIONS = en.ts fr.ts

include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()
