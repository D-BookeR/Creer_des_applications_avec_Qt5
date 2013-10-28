#include <QtQuick/QtQuick>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "abstractobject.h"
#include "abstractcase.h"
#include "cases.h"
#include "human.h"
#include "builder.h"

static QObject *createBuilder(QQmlEngine*, QJSEngine *)
{
    return new Builder;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<AbstractUnit>();
    qmlRegisterUncreatableType<Gender>("MyLib", 1, 0, "Gender", "Uncreatable");
    qmlRegisterType<Human>("MyLib", 1, 0, "Human");
    qmlRegisterType<Forest>("MyLib", 1, 0, "Forest");
    qmlRegisterType<Ground>("MyLib", 1, 0, "Ground");
    qmlRegisterSingletonType<Builder>("MyLib", 1, 0, "Builder", &createBuilder);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/4-noninstanciabletypes/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
