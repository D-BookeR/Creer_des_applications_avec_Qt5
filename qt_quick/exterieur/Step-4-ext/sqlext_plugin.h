#ifndef SQLEXT_PLUGIN_H
#define SQLEXT_PLUGIN_H

#include <QQmlExtensionPlugin>

class SQLExtPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // SQLEXT_PLUGIN_H
