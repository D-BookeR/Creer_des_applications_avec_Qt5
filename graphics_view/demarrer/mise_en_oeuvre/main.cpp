#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsItem>

class RectItemAntialiased: public QGraphicsRectItem
{
public:
    RectItemAntialiased(QGraphicsItem* parent = 0) : QGraphicsRectItem(parent){}

    QRectF boundingRect() const {return rect();}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
    {
        painter->save();

        QBrush brush(Qt::blue);
        painter->setBrush(brush);
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->drawRect(rect());

        painter->restore();
    }
};

class EllipseItemAntialiased: public QGraphicsEllipseItem
{
public:
    EllipseItemAntialiased(QGraphicsItem* parent = 0) : QGraphicsEllipseItem(parent){}

    QRectF boundingRect() const {return rect();}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
    {
        painter->save();

        QBrush brush(Qt::green);
        painter->setBrush(brush);
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->drawEllipse(rect());

        painter->restore();
    }
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QGraphicsScene scene;
	QGraphicsView view(&scene);

    // Insertion d'un rectangle et d'une ellipse
    {
        QGraphicsRectItem *rect = new QGraphicsRectItem(0.0, 0.0, 100.0, 80.0);
        rect->setBrush(Qt::blue);
        rect->setPos(20.0, 30.0);
        scene.addItem(rect);

        QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(0.0, 0.0, 60.0, 60.0);
        ellipse->setBrush(Qt::green);
        scene.addItem(ellipse);
    }

    // Ellipse avec opacité à 50% et création de l'objet par la scène
    {
        scene.addRect(20.0 + 150.0, 30.0, 100.0, 80.0, QPen(), QBrush(Qt::blue));

        QGraphicsEllipseItem *ellipse = scene.addEllipse(150.0, 0.0, 60.0, 60.0, QPen(), QBrush(Qt::green));
        ellipse->setOpacity(0.5);
    }

    // Classe dérivée et utilisation de l'antialiasing dans la mèthode paint
    {
        RectItemAntialiased *rect = new RectItemAntialiased();
        rect->setRect(20.0 + 300.0, 30.0, 100.0, 80.0);
        scene.addItem(rect);

        EllipseItemAntialiased *ellipse = new EllipseItemAntialiased();
        ellipse->setRect(300.0, 0.0, 60.0, 60.0);
        scene.addItem(ellipse);
    }

    view.show();

	return a.exec();
}
