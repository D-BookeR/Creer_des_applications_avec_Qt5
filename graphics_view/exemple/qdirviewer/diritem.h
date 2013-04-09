#ifndef DIRITEM_H
#define DIRITEM_H

#include <QGraphicsRectItem>
#include "dirdata.h"

//@extract-start Qt-commun-QGraphicsView-ex-diritem-h
class DirItem : public QGraphicsRectItem
{

public:
    DirItem(DirData *dir, const QRectF &rect, QGraphicsItem *parent = 0);

    const DirData* dirData() { return m_Dir; }

protected:
    virtual void hoverEnterEvent (QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent *event);

private:
    const DirData *m_Dir;
};
//@extract-end

#endif // DIRITEM_H
