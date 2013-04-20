#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>

#include "navigationwidget.h"

NavigationWidget::NavigationWidget(QGraphicsView *parent) :
    QFrame(parent)
{
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setLineWidth(1);

    QPoint topLeft = parent->mapFromScene(parent->sceneRect().topLeft());
    QPoint bottomRight = parent->mapFromScene(parent->sceneRect().bottomRight());
    m_bgRect = QRect(topLeft, bottomRight);

    setGeometry(m_bgRect);
}

void NavigationWidget::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    QPoint relCursorPos = mapFromGlobal(QCursor::pos());
    QPoint newPos = pos() + relCursorPos - rect().center();

    newPos.setX(qBound(m_bgRect.x(), newPos.x(), m_bgRect.right() - width()));
    newPos.setY(qBound(m_bgRect.y(), newPos.y(), m_bgRect.bottom() - height()));

    move(newPos);

    emit moved(QRect(newPos, size()), m_bgRect);
}

void NavigationWidget::slotNavigateTo(QRectF navRect, QRectF bgRect)
{
    QRect newRect;

    newRect.setLeft(m_bgRect.left() + (navRect.left() - m_bgRect.left()) * m_bgRect.width() / bgRect.width());
    newRect.setTop(m_bgRect.top() + (navRect.top() - m_bgRect.top()) * m_bgRect.height() / bgRect.height());

    if (navRect.height() < bgRect.height()) {
        newRect.setHeight(m_bgRect.height() * navRect.height() / bgRect.height());
    }
    if (navRect.width() < bgRect.width()) {
        newRect.setWidth(m_bgRect.width() * navRect.width() / bgRect.width());
    }

    setGeometry(newRect);
}
