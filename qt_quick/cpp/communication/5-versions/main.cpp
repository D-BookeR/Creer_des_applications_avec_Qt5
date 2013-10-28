#include <QtQuick/QtQuick>
#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "element.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Décommentez les lignes suivantes pour activer la version 1.0 :
    // qmlRegisterRevision<Base, 1>("MyLib", 1, 0);
    // qmlRegisterType<Element, 1>("MyLib", 1, 0, "Element");

    // Commentez les lignes suivantes pour désactiver la version 2.0 :
    // La ligne suivante est utilisée pour accéder à la propriété name de Base :
    qmlRegisterRevision<Base, 1>("MyLib", 2, 0);
    qmlRegisterType<Element, 2>("MyLib", 2, 0, "Element");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/5-versions/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
