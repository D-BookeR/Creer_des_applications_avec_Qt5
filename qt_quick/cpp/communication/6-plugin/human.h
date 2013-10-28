#ifndef HUMAN_H
#define HUMAN_H

#include <QQuickItem>

class Human : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Human)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int hp READ getHp WRITE setHp NOTIFY hpChanged)

public:
    Human(QQuickItem *parent = NULL);
    virtual ~Human();

signals:
    void nameChanged();
    void hpChanged();

private slots:
    QString getName() const { return m_name; }
    void setName(const QString &name) {
        m_name = name;
        emit nameChanged();
    }

    int getHp() const { return m_hp; }
    void setHp(int hp) {
        m_hp = hp;
        emit hpChanged();
    }

private:
    QString m_name;
    int m_hp;
};

QML_DECLARE_TYPE(Human)

#endif // HUMAN_H
