#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QtCore/QPointer>
#include <QtCore/QTranslator>
#include <QtCore/QObject>

class Translation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language NOTIFY languageChanged)

public:
    explicit Translation(QObject *parent = NULL);
    virtual ~Translation();

    Q_INVOKABLE void setLanguage(const QString &l);

signals:
    void languageChanged();

private slots:
    QString language() const;

private:
    QPointer<QTranslator> m_translator;
};

#endif // TRANSLATION_H
