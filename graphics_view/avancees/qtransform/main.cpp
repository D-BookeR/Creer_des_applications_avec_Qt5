#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsItem>

QGraphicsPixmapItem* drawPixmap()
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(":/img/qt-logo.jpg"));

	return item;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QGraphicsScene scene;
	QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setMinimumHeight(200);

    QTransform t0;
    t0.scale(1.0, 1.0);

    QTransform t1;
    t1.shear(0.0, 0.5);

    QTransform t2;
    t2.rotate(45.0, Qt::ZAxis);

    QTransform t3;
    t3 = t1*t2;

    QList<QTransform> list;
    list	<< t0
            << t1
            << t2
            << t3
            ;

	int padding = 0;
    for(int i = 0; i < list.size(); ++i)
	{
        QGraphicsItem *item = drawPixmap();
        item->setTransform(list.at(i));
        scene.addItem(item);
        item->setPos(padding, 0);
        padding += item->boundingRect().width() + 100;
	}

	view.show();

	return a.exec();
}
