#ifndef OBJECTBUILDER_H
#define OBJECTBUILDER_H

#include <QtCore/QObject>

class Forest;
class Ground;
class Human;

class Builder : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE Forest *createForest() const;
    Q_INVOKABLE Ground *createGround() const;
    Q_INVOKABLE Human *createHuman() const;
};

#endif // OBJECTBUILDER_H
