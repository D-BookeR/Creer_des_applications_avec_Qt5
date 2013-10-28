#include "human.h"

Human::Human(QQuickItem *parent)
    : QQuickItem(parent),
      m_name("Unknown"),
      m_hp(100)
{
}

Human::~Human()
{
}
