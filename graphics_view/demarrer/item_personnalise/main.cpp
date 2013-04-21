#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsItem>

//---------------------------- FileItem -------------------------
class FileItem : public QGraphicsItem
{
public:
    FileItem (QGraphicsItem *parent = 0) : QGraphicsItem(parent) {}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
    {
        static const QPointF points[5] =
        {
            QPointF(40.0,  0.0),
            QPointF(0.0,   0.0),
            QPointF(0.0,  70.0),
            QPointF(60.0, 70.0),
            QPointF(60.0, 20.0)
        };

        painter->save();

        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(QPen(Qt::black, 2));
        painter->setBrush(Qt::white);

        painter->drawPolygon(points, 5);
        painter->drawLine( QPointF(60.0, 20.0),
                           QPointF(40.0, 20.0) );
        painter->drawLine( QPointF(40.0, 20.0),
                           QPointF(40.0,  0.0) );

        painter->restore();
    }

    QRectF boundingRect() const
    {
        return QRectF(-1.0, -1.0, 60.0 + 2.0, 70.0 + 2.0);
    }
};
//---------------------------------------------------------------

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QGraphicsScene scene;
	QGraphicsView view(&scene);

    FileItem *item = new FileItem();
    scene.addItem(item);

    view.show();

	return a.exec();
}
