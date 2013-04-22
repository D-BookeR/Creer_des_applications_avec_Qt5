#ifndef FILEITEMBASIC_H
#define FILEITEMBASIC_H

#include <QGraphicsItem>

class FileItemBasic : public QGraphicsItem
{
public:
    FileItemBasic (QGraphicsItem *parent = 0);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QRectF boundingRect() const;
};

#endif // FILEITEMBASIC_H
