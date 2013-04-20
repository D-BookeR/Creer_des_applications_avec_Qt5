#include "dirdata.h"

#include <QDir>
#include <QMimeDatabase>

static void addSize(QMap<QString, qint64> &m, QString key, qint64 value)
{
    if (!m.contains(key)) {
        m.insert(key, value);
    }
    else {
        m.insert(key, m.value(key) + value);
    }
}

DirData::DirData(QString name, DirData *parent) :
    m_Name(name),
    m_Size(0),
    m_MimeDB(NULL),
    m_Parent(parent)
{}

DirData::~DirData()
{
    if (!m_Parent && m_MimeDB) {
        delete m_MimeDB;
    }
    foreach (DirData *d, m_SubDirs) {
        delete d;
    }
}

void DirData::load(QString path)
{
    m_MimeDB = m_Parent ? m_Parent->m_MimeDB : new QMimeDatabase();

    QDir dir(path);
    m_Name = m_Parent ? dir.dirName() : path;
    QFileInfoList fileList = dir.entryInfoList(
        QDir::NoSymLinks | QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot, QDir::Size);

    foreach (const QFileInfo f, fileList) {
        if (!f.isDir() && f.size() > 0) {
            QMimeType mimeType = m_MimeDB->mimeTypeForFile(f);
            FileData fd(f.size(), mimeType.name(), f.fileName());
            m_Files.append(fd);
        }
    }

     foreach (const QFileInfo f, fileList) {
        if (f.isDir()) {
            DirData *subDir = new DirData(f.fileName(), this);
            m_SubDirs.append(subDir);
        }
     }
}

qint64 DirData::filesSize() const
{
    qint64 size = 0;
    foreach (const FileData &f, files()) {
        size += f.size();
    }
    return size;
}

qint64 DirData::size(QString type) const
{
    if (m_Size != 0 && type.isEmpty()) {
        return m_Size;
    }

    qint64 filesSize = 0;
    foreach (const FileData f, m_Files) {
        if (type.isEmpty() || f.type() == type) {
            filesSize += f.size();
        }
    }

    qint64 subDirsSize = 0;
    foreach (DirData *d, m_SubDirs) {
        subDirsSize += d->size(type);
    }

    qint64 res = filesSize + subDirsSize;

    if (type.isEmpty()) {
        m_Size = res;
    }
    return res;
}

qint64 DirData::fileCount() const
{
    qint64 subDirsCount = 0;

    foreach (DirData *d, m_SubDirs) {
        subDirsCount += d->fileCount();
    }

    return m_Files.size() + subDirsCount;
}

QMap<QString, qint64> DirData::typeSizes() const
{
    QMap<QString, qint64> res;

    foreach (const FileData f, m_Files) {
        addSize(res, f.type(), f.size());
    }

    foreach (DirData *d, m_SubDirs) {
        QMap<QString, qint64> subdirSizes  = d->typeSizes();

        QMapIterator<QString, qint64> itSubDirSizes(subdirSizes);
        while (itSubDirSizes.hasNext()) {
            itSubDirSizes.next();
            addSize(res, itSubDirSizes.key(), itSubDirSizes.value());
        }
    }

    return res;
}

QString DirData::path() const
{
    return m_Parent ? m_Parent->path() + '/' + m_Name
                    : m_Name;
}
