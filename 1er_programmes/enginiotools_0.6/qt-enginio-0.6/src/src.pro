requires(qtHaveModule(network))

TEMPLATE = subdirs

QMAKE_DOCS = $$PWD/../doc/qtenginio.qdocconf
load(qt_docs)

CONFIG += ordered

SUBDIRS += enginio_client

qtHaveModule(quick) {
    SUBDIRS += enginio_plugin
}
