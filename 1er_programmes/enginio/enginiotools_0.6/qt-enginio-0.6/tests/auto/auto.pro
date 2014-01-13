TEMPLATE = subdirs

SUBDIRS += \
    enginioclient \
    enginiomodel \
    files \
    notifications \

qtHaveModule(quick) {
    SUBDIRS += qmltests
}
