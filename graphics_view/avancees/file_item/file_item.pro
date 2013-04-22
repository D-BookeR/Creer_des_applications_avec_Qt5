QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = file_item
TEMPLATE = app
SOURCES += main.cpp \
    fileitembasic.cpp \
    fileitemadvanced.cpp

HEADERS += \
    fileitembasic.h \
    fileitemadvanced.h
