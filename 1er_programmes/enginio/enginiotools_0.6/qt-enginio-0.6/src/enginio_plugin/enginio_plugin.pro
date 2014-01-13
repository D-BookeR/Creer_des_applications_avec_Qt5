requires(qtHaveModule(quick))

TARGETPATH = Enginio

QT += qml quick enginio enginio-private

load(qml_plugin)

TARGET = enginioplugin
TARGET.module_name = Enginio

SOURCES += \
    enginioqmlclient.cpp \
    enginioqmlmodel.cpp \
    enginioplugin.cpp \
    enginioqmlreply.cpp \

HEADERS += \
    enginioqmlclient.h \
    enginioqmlmodel.h \
    enginioplugin.h \
    enginioqmlobjectadaptor_p.h \
    enginioqmlclient_p.h \
    enginioqmlreply.h \

QMLDIRFILE = $${_PRO_FILE_PWD_}/qmldir

macx|win32 {
    DESTDIR = ../../qml/$${TARGET.module_name}
    TARGET = $$TARGET$$qtPlatformTargetSuffix()
}

copy2build.input = QMLDIRFILE
copy2build.output = ../../qml/$${TARGET.module_name}/qmldir
!contains(TEMPLATE_PREFIX, vc):copy2build.variable_out = PRE_TARGETDEPS
copy2build.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy2build.name = COPY ${QMAKE_FILE_IN}
copy2build.CONFIG += no_link
force_independent: QMAKE_EXTRA_COMPILERS += copy2build
