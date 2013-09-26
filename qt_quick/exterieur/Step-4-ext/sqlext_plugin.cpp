#include "sqlext_plugin.h"
#include "sqlext.h"
#include <qqml.h>

static QObject *sqlExtProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new SQLExt();
}

void SQLExtPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<SQLExtDatabase>();
    qmlRegisterSingletonType<SQLExt>(uri, 1, 0, "SQLExt", &sqlExtProvider);
}
