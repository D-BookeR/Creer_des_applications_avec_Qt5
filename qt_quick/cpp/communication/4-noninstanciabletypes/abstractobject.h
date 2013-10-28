#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include <QtCore/QUrl>
#include <QtCore/QPoint>
#include <QtCore/QObject>

class AbstractObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl resource READ getResource NOTIFY resourceChanged)
    Q_PROPERTY(QPoint position READ getPosition WRITE setPosition NOTIFY positionChanged)

public:
    AbstractObject(QObject *parent = NULL);
    virtual ~AbstractObject() {}

signals:
    void resourceChanged();
    void positionChanged();

protected slots:
    virtual QUrl getResource() const = 0;

public slots:
    QPoint getPosition() const;
    void setPosition(const QPoint &p);

private:
    QPoint m_position;
};

#endif // ABSTRACTOBJECT_H
