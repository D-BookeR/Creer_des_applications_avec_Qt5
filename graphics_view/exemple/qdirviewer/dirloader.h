#ifndef DIRLOADER_H
#define DIRLOADER_H

#include <QObject>

//@extract-start Qt-commun-QGraphicsView-ex-dirloader-h
class DirData;

class DirLoader : public QObject
{
    Q_OBJECT
public:
    explicit DirLoader(DirData *dirData, QString path);

    void load();
    void stop();

signals:
    void signalDirContentLoaded(qint64 size);
    void signalLoadFinished(QString path);

private:
    void        loadDir(QString path, DirData *dirData);

    bool        m_Stop;
    DirData    *m_DirData;
    QString     m_Path;
};
//@extract-end

#endif // DIRLOADER_H
