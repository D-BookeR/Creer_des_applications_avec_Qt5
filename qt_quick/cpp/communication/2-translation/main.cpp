#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "translation.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Translation tr;

    QtQuick2ApplicationViewer viewer;
    viewer.engine()->rootContext()->setContextProperty("tr", &tr);
    viewer.setMainQmlFile(QStringLiteral("qml/2-translation/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
