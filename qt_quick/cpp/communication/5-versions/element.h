#ifndef ELEMENT_H
#define ELEMENT_H

#include <QtCore/QObject>

class Base : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged REVISION 1)

public:
    Base(QObject *parent = NULL)
        : QObject(parent),
          m_name("Base")
    {
    }
    virtual ~Base() {}

signals:
    Q_REVISION(1) void nameChanged();

public slots:
    Q_REVISION(1) QString getName() const { return m_name; }
    Q_REVISION(1) void setName(const QString &name) {
        m_name = name;
        emit nameChanged();
    }

private:
    QString m_name;
};

class Element : public Base
{
    Q_OBJECT
    Q_PROPERTY(int cost READ getCost WRITE setCost NOTIFY costChanged REVISION 1)
    Q_PROPERTY(int size READ getSize WRITE setSize NOTIFY sizeChanged REVISION 2)

public:
    Element(QObject *parent = NULL)
        : Base(parent),
          m_cost(0),
          m_size(0)
    {
    }

signals:
    Q_REVISION(1) void costChanged();
    Q_REVISION(2) void sizeChanged();

public slots:
    Q_REVISION(1) int getCost() const { return m_cost; }
    Q_REVISION(2) int getSize() const { return m_size; }
    Q_REVISION(1) void setCost(int value) {
        m_cost = value;
        emit costChanged();
    }
    Q_REVISION(2) void setSize(int value) {
        m_size = value;
        emit sizeChanged();
    }

private:
    int m_cost;
    int m_size;
};

#endif // ELEMENT_H
