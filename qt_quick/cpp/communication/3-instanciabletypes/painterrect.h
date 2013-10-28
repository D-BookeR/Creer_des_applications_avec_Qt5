#ifndef PAINTERRECT_H
#define PAINTERRECT_H

#include <QtQuick/QtQuick>

class PainterRect : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    PainterRect(QQuickItem *parent = NULL);
    virtual ~PainterRect() {}

protected:
    virtual void paint(QPainter *painter);

signals:
    void colorChanged();

private slots:
    QColor color() const { return m_color; }
    void setColor(const QColor &c);

private:
    QColor m_color;
};

#endif // PAINTERRECT_H
