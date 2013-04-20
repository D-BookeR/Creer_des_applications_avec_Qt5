#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class FileData;
class DirData;

class View : public QGraphicsView
{
public:
    Q_OBJECT

public:
    View(QGraphicsScene *scene);

    void zoom(int delta);
    void notifyFileChanged(const FileData *file);
    void notifyDirChanged(const DirData *dir);
    static View* getView(QGraphicsItem *item);

signals:
    void displayChanged(QRectF visibleRect, QRectF contentsRect);
    void fileChanged(const FileData *file);
    void dirChanged(const DirData *file);

public slots:
    void slotNavigateTo(QRect navRect, QRect bgRect);

protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void resizeEvent (QResizeEvent *event);
    virtual void scrollContentsBy (int dx, int dy);
};

#endif // VIEW_H
