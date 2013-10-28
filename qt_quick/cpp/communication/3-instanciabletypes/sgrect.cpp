#include "sgrect.h"

SGRect::SGRect(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(QQuickItem::ItemHasContents);
}

QSGNode *SGRect::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGSimpleRectNode *node = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!node) {
        node = new QSGSimpleRectNode();
    }
    node->setColor(m_color);
    node->setRect(boundingRect());
    return node;
}

void SGRect::setColor(const QColor &c)
{
    m_color = c;
    update();
    emit colorChanged();
}
