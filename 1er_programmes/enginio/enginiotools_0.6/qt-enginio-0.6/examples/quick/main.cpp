#include <QApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QDir>

#include "backendhelper.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    QQuickView view;
    const QString appPath = QCoreApplication::applicationDirPath();

    // This allows starting the example without previously defining QML2_IMPORT_PATH.
    QDir qmlImportDir(appPath);
#if defined (Q_OS_WIN)
    qmlImportDir.cd("..");
#endif
    qmlImportDir.cd("../../../qml");
    view.engine()->addImportPath(qmlImportDir.canonicalPath());
    QObject::connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));

    QPair<QByteArray, QByteArray> backendData = backendIdAndSecret(ENGINIO_SAMPLE_NAME);
    view.engine()->rootContext()->setContextProperty("enginioBackendId", backendData.first);
    view.engine()->rootContext()->setContextProperty("enginioBackendSecret", backendData.second);

    view.setSource(QUrl("qrc:///" ENGINIO_SAMPLE_NAME ".qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();
    return app.exec();
}
