#ifndef ABSTRACTCASE_H
#define ABSTRACTCASE_H

#include <QtCore/QObject>
#include "abstractobject.h"
#include "abstractunit.h"

class AbstractCase : public AbstractObject
{
    Q_OBJECT
    Q_PROPERTY(int cost READ getCost)
    Q_PROPERTY(AbstractUnit *unit READ getUnit WRITE setUnit NOTIFY unitChanged)

public:
    AbstractCase(QObject *parent = NULL);
    virtual ~AbstractCase() {}

signals:
    void unitChanged();

protected slots:
    virtual int getCost() const = 0;

private slots:
    AbstractUnit *getUnit() const;
    void setUnit(AbstractUnit *u);

private:
    AbstractUnit *m_unit;
};

QML_DECLARE_TYPE(AbstractCase)

#endif // ABSTRACTCASE_H
