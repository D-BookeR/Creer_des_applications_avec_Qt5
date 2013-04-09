#include "diritem.h"
#include "mainwindow.h"
#include "view.h"

//@extract-start Qt-commun-QGraphicsView-ex-diritem-cpp
DirItem::DirItem(DirData *dir, const QRectF &rect, QGraphicsItem *parent) :
    QGraphicsRectItem(rect, parent), m_Dir(dir)
{
    setAcceptHoverEvents(true);
}

void DirItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    setBrush(QBrush(Qt::yellow));
    View::getView(this)->notifyDirChanged(m_Dir);
}

void DirItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    setBrush(QBrush(Qt::NoBrush));
    View::getView(this)->notifyDirChanged(NULL);
}
//@extract-end
