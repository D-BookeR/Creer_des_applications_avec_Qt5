#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtWidgets/QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickView* view = new QQuickView();
    view->setSource(QUrl("./main.qml"));

    QWidget* container = QWidget::createWindowContainer(view);
    container->setMinimumSize(248, 460);
    container->setMaximumSize(248, 460);
    container->setFocusPolicy(Qt::TabFocus);
    container->show();

    return app.exec();
}
