#include <QtCore/QUrl>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QUrl url("http://www.d-booker.fr/");

    QtQuick2ApplicationViewer viewer;
    viewer.engine()->rootContext()->setContextProperty("website", url);
    viewer.setMainQmlFile(QStringLiteral("qml/1-contextproperties/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
