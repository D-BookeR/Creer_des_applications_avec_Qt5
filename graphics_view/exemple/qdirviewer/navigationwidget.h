#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H

#include <QFrame>

class QGraphicsView;

//@extract-start Qt-commun-QGraphicsView-ex-navigationwidget-h
class NavigationWidget : public QFrame
{
    Q_OBJECT
public:
    explicit NavigationWidget(QGraphicsView *parent);

signals:
    void moved(QRect newRect, QRect bgRect);

public slots:
    void slotNavigateTo(QRectF navRect, QRectF bgRect);

protected:
    virtual void mouseMoveEvent (QMouseEvent *event);

private:
    QRect   m_bgRect;
};
//@extract-end

#endif // NAVIGATIONWIDGET_H
