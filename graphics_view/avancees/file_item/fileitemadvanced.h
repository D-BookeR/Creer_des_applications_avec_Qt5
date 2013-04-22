#ifndef FILEITEMADVANCED_H
#define FILEITEMADVANCED_H

#include <QGraphicsItem>

class FileItemAdvanced : public QGraphicsItem
{
public:
    FileItemAdvanced (QGraphicsItem *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    bool               m_bDragOver;
    QGraphicsTextItem *m_textItem;
};

#endif // FILEITEMADVANCED_H
