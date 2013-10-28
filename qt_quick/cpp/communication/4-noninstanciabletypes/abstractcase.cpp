#include "abstractcase.h"

AbstractCase::AbstractCase(QObject *parent)
    : AbstractObject(parent),
      m_unit(NULL)
{
}

AbstractUnit *AbstractCase::getUnit() const
{
    return m_unit;
}

void AbstractCase::setUnit(AbstractUnit *u)
{
    m_unit = u;
    emit unitChanged();
}
