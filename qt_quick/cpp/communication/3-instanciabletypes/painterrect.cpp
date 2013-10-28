#include "painterrect.h"

PainterRect::PainterRect(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      m_color(Qt::white)
{
}

void PainterRect::paint(QPainter *painter)
{
    painter->save();
    painter->setBrush(m_color);
    painter->setPen(QColor(Qt::transparent));
    painter->drawRect(boundingRect());
    painter->restore();
}

void PainterRect::setColor(const QColor &c)
{
    m_color = c;
    update();
    emit colorChanged();
}
