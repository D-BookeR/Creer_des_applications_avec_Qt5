#ifndef FILEITEM_H
#define FILEITEM_H

#include <QGraphicsRectItem>
#include "filedata.h"

class View;

class FileItem : public QGraphicsRectItem
{
public:
    FileItem(const FileData *file, const QRectF &rect, QGraphicsItem *parent = 0);

    QString fileName() const { return m_File->name(); }
    static QColor colorFromType(QString type);

protected:
    virtual void hoverEnterEvent (QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent *event);    

private:
    const FileData *m_File;
};

#endif // FILEITEM_H
