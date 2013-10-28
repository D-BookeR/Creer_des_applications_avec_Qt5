#include <QtQuick/QtQuick>
#include "human_plugin.h"
#include "human.h"

void HumanPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    engine->rootContext()->setContextProperty("pluginUri", uri);
}

void HumanPlugin::registerTypes(const char *uri)
{
    // @uri Human
    qmlRegisterType<Human>(uri, 1, 0, "Human");
}
