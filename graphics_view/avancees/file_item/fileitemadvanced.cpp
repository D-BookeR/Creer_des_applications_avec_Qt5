#include "fileitemadvanced.h"

#include <QPainter>
#include <QMimeData>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneDragDropEvent>

FileItemAdvanced::FileItemAdvanced(QGraphicsItem *parent)
: QGraphicsItem(parent),
  m_bDragOver(false)
{
    setAcceptDrops(true);
    setFlag(QGraphicsItem::ItemClipsChildrenToShape);

    m_textItem = new QGraphicsTextItem(this);
    m_textItem->setTextWidth(60);
    m_textItem->setX(1.0);
    m_textItem->setY(25.0);
}

QRectF FileItemAdvanced::boundingRect() const
{
    return QRectF(-1.0, -1.0, 60.0 + 2.0, 70.0 + 2.0);
}

void FileItemAdvanced::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    m_bDragOver = true;
    update();
    event->accept();
}

void FileItemAdvanced::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    m_bDragOver = false;
    update();
    event->accept();
}

void FileItemAdvanced::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    const QMimeData *data = event->mimeData();
    if (data->hasText()) {
        m_textItem->setPlainText(data->text());
    }

    m_bDragOver = false;
    update();
    event->accept();
}

void FileItemAdvanced::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
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

    if (m_bDragOver) {
        painter->setPen(QPen(Qt::red, 2));
    } else {
        painter->setPen(QPen(Qt::black, 2));
    }

    painter->setBrush(Qt::white);

    painter->drawPolygon(points, 5);
    painter->drawLine(QPointF(60.0, 20.0), QPointF(40.0, 20.0));
    painter->drawLine(QPointF(40.0, 20.0), QPointF(40.0, 0.0));

    painter->restore();
}
