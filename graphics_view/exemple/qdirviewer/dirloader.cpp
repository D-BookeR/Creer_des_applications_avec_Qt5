#include <QMutexLocker>

#include "dirloader.h"
#include "dirdata.h"

QMutex mutex;

DirLoader::DirLoader(DirData *dirData, QString path) :
    m_Stop(false),
    m_DirData(dirData),
    m_Path(path)
{}

void DirLoader::stop()
{
    QMutexLocker locker(&mutex);
    m_Stop = true;
}

void  DirLoader::load()
{
    loadDir(m_Path, m_DirData);
    if (m_Stop) {
        return;
    }

    emit signalLoadFinished(m_Path);
}

void  DirLoader::loadDir(QString path, DirData *dirData)
{
    if (m_Stop) {
        return;
    }
    dirData->load(path);
    emit signalDirContentLoaded(dirData->filesSize());

    foreach (DirData *subDir, dirData->subdirs()) {
        loadDir(subDir->path(), subDir);
    }
}
