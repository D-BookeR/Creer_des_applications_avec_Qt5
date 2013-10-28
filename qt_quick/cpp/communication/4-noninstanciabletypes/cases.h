#ifndef CASETYPES_H
#define CASETYPES_H

#include "abstractcase.h"

class Forest : public AbstractCase
{
public:
    Forest(QObject *parent = NULL);
    virtual ~Forest() {}

protected slots:
    virtual int getCost() const;
    virtual QUrl getResource() const;
};

class Ground : public AbstractCase
{
public:
    Ground(QObject *parent = NULL);
    virtual ~Ground() {}

protected slots:
    virtual int getCost() const;
    virtual QUrl getResource() const;
};

#endif // CASETYPES_H
