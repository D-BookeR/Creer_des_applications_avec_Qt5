#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsPathItem>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsTextItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsProxyWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QLineEdit>
#include <QTransform>

//------------------------ QGraphicsOriginItem ------------------------
class QGraphicsOriginItem: public QGraphicsItem
{
public:
    QGraphicsOriginItem(QGraphicsItem *parent) : QGraphicsItem(parent){}

    QRectF boundingRect() const {return QRectF(-5, 5, 5, 5);}

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
	{
		painter->save();
		painter->setPen(QPen(Qt::black));
		painter->setRenderHint(QPainter::Antialiasing, false);
		painter->drawLine(0, -4, 0, 4);
		painter->drawLine(4, 0, -4, 0);
		painter->restore();
	}
};

void drawOrigin(QGraphicsItem *item)
{
	new QGraphicsOriginItem(item);
}

QGraphicsEllipseItem* drawEllipse()
{
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(QRectF(0.0, 0.0, 130.0, 100.0));
    item->setBrush(Qt::blue);

    return item;
}

QGraphicsPolygonItem* drawPolygon()
{
	QPolygonF polygon;
    polygon << QPointF(20.0, 15.0) << QPointF(40.0, 110.0) << QPointF(90.0, 60.0) << QPointF(140.0, 85.0) << QPointF(60.0, 70.0);

    QGraphicsPolygonItem *item = new QGraphicsPolygonItem(polygon);
	item->setPen(QPen(Qt::gray));
	item->setBrush(Qt::darkMagenta);

	return item;
}

QGraphicsEllipseItem* drawPie()
{
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(QRectF(0.0, 0.0, 100.0, 100.0));
    item->setBrush(Qt::yellow);
    item->setStartAngle(16 * 20);
    item->setSpanAngle(16 * 300);

    return item;
}

QGraphicsPathItem* drawPath()
{
	QPainterPath path;
    path.moveTo(0.0, 0.0);
    path.cubicTo(40.0, 40.0, 50.0, -40.0, 120.0, 30.0);

    QGraphicsPathItem *item = new QGraphicsPathItem();
	item->setPen(QPen(Qt::darkGreen));
	item->setPath(path);

	return item;
}

QGraphicsTextItem* drawText()
{
    QGraphicsTextItem *item = new QGraphicsTextItem();
    item->setHtml("HTML <img src=\":/img/pawn.png\" alt=\"Fou\"></img>");
    item->setFont(QFont("Arial", 22));

	return item;
}

QGraphicsSimpleTextItem* drawSimpleText()
{
    QGraphicsSimpleTextItem *item = new QGraphicsSimpleTextItem("Bonjour Qt");
    item->setFont(QFont("Arial", 26, QFont::Bold));

	return item;
}

QGraphicsPathItem* drawPathComplex()
{
	QPainterPath painterpath;
    QRectF rect(30.0, 30.0, 50.0, 50.0);
	painterpath.addEllipse(rect);
	painterpath.addRect(rect);
    painterpath.addEllipse(rect.bottomRight(), rect.height() / 2.0, rect.height() / 2.0);

    QGraphicsPathItem *item = new QGraphicsPathItem();
	item->setPen(QPen(Qt::black));
	item->setBrush(Qt::darkBlue);
	item->setPath(painterpath);

	return item;
}

QGraphicsPixmapItem* drawPixmap()
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(":/img/pawn.png"));

	return item;
}

QGraphicsRectItem* drawRect()
{
    QGraphicsRectItem *item = new QGraphicsRectItem(10.0, 10.0, 120.0, 70.0);
	QBrush brush;
    brush.setColor(QColor(30, 200, 50));
    brush.setStyle(Qt::DiagCrossPattern);
    item->setBrush(brush);

    return item;
}

QGraphicsLineItem* drawLine()
{
    QGraphicsLineItem *item = new QGraphicsLineItem(1.0, 10.0, 90.0, 100.0);
	QPen pen;
	pen.setWidth(2);
	pen.setBrush(Qt::red);
	pen.setStyle(Qt::DashLine);
    item->setPen(pen);

    return item;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QGraphicsScene scene;
	QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setMinimumHeight(200);

    QList<QGraphicsItem*> list;
	list	<< drawEllipse()
			<< drawPie()
			<< drawLine()
			<< drawRect()
			<< drawPath()
			<< drawPathComplex()
			<< drawPixmap()
			<< drawPolygon()
			<< drawText()
			<< drawSimpleText()
			;

	int padding = 0;
    for(int i = 0; i < list.size(); ++i)
	{
		drawOrigin(list.at(i));
		scene.addItem(list.at(i));
		list.at(i)->setPos(padding, 0);
        padding += list.at(i)->boundingRect().width() + 50;
	}

	view.show();

	return a.exec();
}
