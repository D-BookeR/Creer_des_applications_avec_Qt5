#ifndef DIRDATA_H
#define DIRDATA_H

#include <QVector>
#include <QMap>
#include <QSet>
#include "filedata.h"

class QMimeDatabase;

class DirData
{
public:
    DirData(QString name = "", DirData *parent = NULL);
    ~DirData();

    void                    load(QString path);
    QString                 name() const { return m_Name; }
    QVector<FileData>       files() const { return m_Files; }
    qint64                  filesSize() const;
    QVector<DirData*>       subdirs() const { return m_SubDirs; }
    qint64                  size(QString type = "") const;
    qint64                  fileCount() const;
    QSet<QString>           types() const;
    QMap<QString,qint64>    typeSizes() const;
    QString                 path() const;

private:
    QString                 m_Name;
    QVector<FileData>       m_Files;
    QVector<DirData*>       m_SubDirs;
    QMap<QString,qint64>    m_TypeSizes;
    mutable qint64          m_Size;

    QMimeDatabase          *m_MimeDB;
    DirData                *m_Parent;
};

#endif // DIRDATA_H
