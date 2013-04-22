#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRotation>
#include <QPropertyAnimation>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QGraphicsScene scene;
	QGraphicsView view(&scene);
    view.setMinimumHeight(150);

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(":/img/qt-logo.jpg"));
    scene.addItem(item);

    QGraphicsRotation *rotation = new QGraphicsRotation();
    rotation->setAxis(Qt::ZAxis);
    rotation->setOrigin(QVector3D(QPoint(item->boundingRect().width() / 2.0, item->boundingRect().height() / 2.0)));
    item->setTransformations(QList<QGraphicsTransform *>() << rotation);

    QPropertyAnimation *anim = new QPropertyAnimation(rotation, "angle");
    anim->setDuration(5000);
    anim->setStartValue(0);
    anim->setEndValue(360);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

	view.show();

	return a.exec();
}
