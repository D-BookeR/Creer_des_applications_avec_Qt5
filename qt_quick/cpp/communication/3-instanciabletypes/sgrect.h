#ifndef SGRECT_H
#define SGRECT_H

#include <QtQuick/QtQuick>

class SGRect : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    SGRect(QQuickItem *parent = NULL);
    virtual ~SGRect() {}

protected:
    virtual QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);

signals:
    void colorChanged();

private slots:
    QColor color() const { return m_color; }
    void setColor(const QColor &c);

private:
    QColor m_color;
};

#endif // SGRECT_H
