#ifndef HUMAN_H
#define HUMAN_H

#include <QtCore/QObject>
#include "abstractunit.h"

class Gender : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)
public:
    enum Type { Male = 0, Female };
};

class Human : public AbstractUnit
{
    Q_OBJECT
    Q_PROPERTY(Gender::Type gender READ getGender WRITE setGender NOTIFY genderChanged)

public:
    Human(QObject *parent = NULL);
    virtual ~Human() {}

signals:
    void genderChanged();

protected slots:
    virtual QUrl getResource() const;

public slots:
    Gender::Type getGender() const;
    void setGender(Gender::Type g);

private:
    Gender::Type m_gender;
};

#endif // HUMAN_H
