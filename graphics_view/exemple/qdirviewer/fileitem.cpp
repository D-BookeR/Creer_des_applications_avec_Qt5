#include <QBrush>
#include <QGraphicsSceneHoverEvent>
#include <QDebug>

#include "fileitem.h"
#include "mainwindow.h"
#include "view.h"

FileItem::FileItem(const FileData *file, const QRectF &rect, QGraphicsItem *parent) :
    QGraphicsRectItem(rect, parent),
    m_File(file)
{
    setAcceptHoverEvents(true);
    setBrush(QBrush(colorFromType(file->type())));
}

QColor FileItem::colorFromType(QString type)
{
    quint16 crc = qChecksum(type.toLatin1().constData(), type.size());
    quint16 r = 4 * (crc % 64);
    quint16 g = 8 * ((crc >> 6) % 32);
    quint16 b = 8 * (crc >> 12);

    return QColor(r, g, b);
}

void FileItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    View::getView(this)->notifyFileChanged(m_File);
}

void FileItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    View::getView(this)->notifyFileChanged(NULL);
}
