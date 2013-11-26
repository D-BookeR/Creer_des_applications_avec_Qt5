TARGET = Enginio
QT += network
DEFINES += ENGINIOCLIENT_LIBRARY
MODULE = enginio

load(qt_module)

SOURCES += \
    enginiobackendconnection.cpp \
    enginioclient.cpp \
    enginioreply.cpp \
    enginiomodel.cpp \
    enginioidentity.cpp \
    enginiofakereply.cpp \
    enginiodummyreply.cpp \
    enginiostring.cpp

HEADERS += \
    chunkdevice_p.h \
    enginiobackendconnection_p.h \
    enginioclient.h\
    enginioclient_global.h \
    enginioclient_p.h \
    enginioreply.h \
    enginiomodel.h \
    enginioidentity.h \
    enginioobjectadaptor_p.h \
    enginioreply_p.h \
    enginiofakereply_p.h \
    enginiodummyreply_p.h \
    enginiostring_p.h

