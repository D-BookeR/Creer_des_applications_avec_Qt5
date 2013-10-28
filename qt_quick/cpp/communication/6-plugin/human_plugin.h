#ifndef HUMAN_PLUGIN_H
#define HUMAN_PLUGIN_H

#include <QQmlExtensionPlugin>

class HumanPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    virtual void initializeEngine(QQmlEngine *engine, const char *uri);
    virtual void registerTypes(const char *uri);
};

#endif // HUMAN_PLUGIN_H
