#include <QWheelEvent>
#include <QGraphicsRectItem>
#include <QScrollBar>
#include <QDebug>

#include "view.h"
#include "navigationwidget.h"

//@extract-start Qt-commun-QGraphicsView-ex-construct-view-cpp
View::View(QGraphicsScene *scene) :
    QGraphicsView(scene)
{
    setDragMode(QGraphicsView::ScrollHandDrag);

    fitInView(sceneRect(), Qt::KeepAspectRatioByExpanding);

    QGraphicsView *navigationView = new QGraphicsView(this);
    navigationView->setGeometry(0, 0, 120, 120);
    navigationView->setScene(scene);
    navigationView->setBackgroundBrush(QBrush(0xfcff8b));
    navigationView->fitInView(sceneRect(), Qt::KeepAspectRatioByExpanding);

    NavigationWidget *navWidget = new NavigationWidget(navigationView);
    connect(this, &View::displayChanged, navWidget, &NavigationWidget::slotNavigateTo);
    connect(navWidget, &NavigationWidget::moved, this, &View::slotNavigateTo);
}
//@extract-end

//@extract-start Qt-commun-QGraphicsView-ex-getView-view-cpp
View* View::getView(QGraphicsItem *item)
{
    return static_cast<View *>(item->scene()->views().first());
}

void View::notifyFileChanged(const FileData *file)
{
    emit fileChanged(file);
}

void View::notifyDirChanged(const DirData *dir)
{
    emit dirChanged(dir);
}
//@extract-end

//@extract-start Qt-commun-QGraphicsView-ex-zoom-view-cpp
void View::zoom(int delta)
{
    double zoom = 1.0 + (delta / 1000.0);
    scale(zoom, zoom);
}

void View::wheelEvent(QWheelEvent *event)
{
    zoom(event->delta());
    event->accept();
}
//@extract-end

//@extract-start Qt-commun-QGraphicsView-ex-resizeEvent-view-cpp
void View::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    QRectF visibleRect = QRectF(mapToScene(rect().topLeft()), mapToScene(rect().bottomRight()));
    emit displayChanged(visibleRect, sceneRect());
}
//@extract-end

//@extract-start Qt-commun-QGraphicsView-ex-scrollContentsBy-view-cpp
void View::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx, dy);

    QRectF visibleRect = QRectF(mapToScene(rect().topLeft()), mapToScene(rect().bottomRight()));
    emit displayChanged(visibleRect, sceneRect());
}
//@extract-end

//@extract-start Qt-commun-QGraphicsView-ex-slotNavigateTo-view-cpp
void View::slotNavigateTo(QRect navRect, QRect bgRect)
{
    QScrollBar* bar = horizontalScrollBar();
    qreal sizeRatio = (qreal)(bar->maximum() - bar->minimum()) / (bgRect.width() - navRect.width());
    bar->setValue(bar->minimum() + (ceil(sizeRatio)) * (navRect.x()-bgRect.x()));

    bar = verticalScrollBar();
    sizeRatio = (qreal)(bar->maximum() - bar->minimum()) / (bgRect.height() - navRect.height());
    bar->setValue(bar->minimum() + (ceil(sizeRatio)) * (navRect.y()-bgRect.y()));
}
//@extract-end
