#include "abstractobject.h"

AbstractObject::AbstractObject(QObject *parent)
    : QObject(parent),
      m_position()
{
}

QPoint AbstractObject::getPosition() const
{
    return m_position;
}

void AbstractObject::setPosition(const QPoint &p)
{
    m_position = p;
}
