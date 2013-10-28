#include "abstractunit.h"

AbstractUnit::AbstractUnit(QObject *parent)
    : AbstractObject(parent),
      m_movement(4)
{
}

int AbstractUnit::getMovement() const
{
    return m_movement;
}

void AbstractUnit::setMovement(int mvt)
{
    m_movement = mvt;
    emit movementChanged();
}
