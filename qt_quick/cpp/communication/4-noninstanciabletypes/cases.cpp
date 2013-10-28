#include <QtCore/QCoreApplication>
#include "cases.h"

Forest::Forest(QObject *parent)
    : AbstractCase(parent)
{
}

int Forest::getCost() const
{
    return 2;
}

QUrl Forest::getResource() const
{
    return QUrl("qrc:/forest.png");
}

Ground::Ground(QObject *parent)
    : AbstractCase(parent)
{
}

int Ground::getCost() const
{
    return 1;
}

QUrl Ground::getResource() const
{
    return QUrl("qrc:/ground.png");
}
