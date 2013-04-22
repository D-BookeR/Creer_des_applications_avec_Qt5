#include "fileitembasic.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

FileItemBasic::FileItemBasic(QGraphicsItem *parent)
: QGraphicsItem(parent)
{}

QRectF FileItemBasic::boundingRect() const
{
    return QRectF(-1.0, -1.0, 60.0 + 2.0, 70.0 + 2.0);
}

void FileItemBasic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
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

    if (option->state & QStyle::State_Selected) {
        painter->setBrush(QColor(10,230,50));
    } else {
        painter->setBrush(Qt::white);
    }

    painter->drawPolygon(points, 5);
    painter->drawLine(QPointF(60.0, 20.0), QPointF(40.0, 20.0));
    painter->drawLine(QPointF(40.0, 20.0), QPointF(40.0, 0.0));

    if (option->state & QStyle::State_MouseOver)
    {
        painter->setPen(QPen(Qt::black, 4));
        //On dessine un "+"
        painter->drawLine(QPointF(10.0, 50.0), QPointF(30.0, 50.0));
        painter->drawLine(QPointF(20.0, 40.0), QPointF(20.0, 60.0));
    }

    painter->restore();
}
