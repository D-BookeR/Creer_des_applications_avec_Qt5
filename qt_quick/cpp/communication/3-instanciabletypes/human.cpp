#include "human.h"

Human::Human(QObject *parent)
    : QObject(parent),
      m_name(""),
      m_age(0),
      m_size(0)
{
}

void Human::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}

void Human::setAge(int age)
{
    m_age = age;
    emit ageChanged();
}

void Human::setSize(int size)
{
    m_size = size;
    emit sizeChanged();
}
