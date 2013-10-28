#ifndef ABSTRACTUNIT_H
#define ABSTRACTUNIT_H

#include <QtQuick/QtQuick>
#include "abstractobject.h"

class AbstractUnit : public AbstractObject
{
    Q_OBJECT
    Q_PROPERTY(int movement READ getMovement WRITE setMovement NOTIFY movementChanged)

public:
    AbstractUnit(QObject *parent = NULL);
    virtual ~AbstractUnit() {}

signals:
    void movementChanged();

protected slots:
    int getMovement() const;
    void setMovement(int mvt);

private:
    int m_movement;
};

#endif // ABSTRACTUNIT_H
