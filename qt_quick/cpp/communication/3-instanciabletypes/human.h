#ifndef HUMAN_H
#define HUMAN_H

#include <QObject>

class Human : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)

public:
    explicit Human(QObject *parent = NULL);
    virtual ~Human() {}

signals:
    void nameChanged();
    void ageChanged();
    void sizeChanged();

private slots:
    QString name() const { return m_name; }
    int age() const { return m_age; }
    int size() const { return m_size; }

    void setName(const QString &name);
    void setAge(int age);
    void setSize(int size);

private:
    QString m_name;
    int m_age;
    int m_size;
};

#endif // HUMAN_H
