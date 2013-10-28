#include <QtGui/QGuiApplication>
#include <QtCore/QScopedPointer>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl::fromLocalFile("main.qml"));
    QObject* object = component.create(engine.rootContext());
    QScopedPointer<QQuickWindow> window(qobject_cast<QQuickWindow *>(object));
    window->show();

    return app.exec();
}
