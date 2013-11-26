QT       += testlib enginio enginio-private
QT       -= gui

DEFINES += TEST_FILE_PATH=\\\"$$_PRO_FILE_PWD_/../common/enginio.png\\\"

TARGET = tst_files
CONFIG   += console testcase
CONFIG   -= app_bundle

include(../common/common.pri)

TEMPLATE = app

SOURCES += tst_files.cpp