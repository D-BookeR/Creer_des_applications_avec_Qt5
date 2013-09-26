QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Koch
TEMPLATE = app


SOURCES += main.cpp\
	   widget.cpp \
	   controles.cpp \
	   processeur.cpp

HEADERS  += widget.h \
	    controles.h \
	    processeur.h

FORMS    += \
	    controles.ui
