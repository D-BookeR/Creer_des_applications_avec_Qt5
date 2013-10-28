#include <QtCore/QCoreApplication>
#include "human.h"

Human::Human(QObject *parent)
    : AbstractUnit(parent),
      m_gender(Gender::Male)
{
}

QUrl Human::getResource() const
{
    return QUrl("qrc:/unit.png");
}

Gender::Type Human::getGender() const
{
    return m_gender;
}

void Human::setGender(Gender::Type g)
{
    m_gender = g;
    emit genderChanged();
}
