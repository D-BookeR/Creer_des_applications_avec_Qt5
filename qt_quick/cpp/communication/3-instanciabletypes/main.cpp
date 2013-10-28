#include <QtQml>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "human.h"
#include "painterrect.h"
#include "sgrect.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Human>("MyLib", 1, 0, "Human");
    qmlRegisterType<SGRect>("MyLib", 1, 0, "SGRect");
    qmlRegisterType<PainterRect>("MyLib", 1, 0, "PainterRect");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/3-instanciabletypes/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
