#include <QtCore/QDebug>
#include <QtGui/QGuiApplication>
#include "translation.h"

Translation::Translation(QObject *parent)
    : QObject(parent)
{
    setLanguage("en");
}

Translation::~Translation()
{
}

QString Translation::language() const
{
    return "";
}

void Translation::setLanguage(const QString &l)
{
    if (m_translator)
        qApp->removeTranslator(m_translator);

    m_translator = new QTranslator;
    const QString path = qApp->applicationDirPath() + "/" + l;
    if (!m_translator->load(path)) {
        qDebug() << "Error: could not load" << qPrintable(path);
        return;
    }

    qApp->installTranslator(m_translator);
    emit languageChanged();
}
