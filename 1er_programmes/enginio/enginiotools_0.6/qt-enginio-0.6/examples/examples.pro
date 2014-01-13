TEMPLATE = subdirs

qtHaveModule(quick) {
    SUBDIRS += quick
}
qtHaveModule(widgets) {
    SUBDIRS += widgets
}
