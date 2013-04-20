#ifndef NAVIGATIONWIDGET_H
#define NAVIGATIONWIDGET_H

#include <QFrame>

class QGraphicsView;

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

#endif // NAVIGATIONWIDGET_H
