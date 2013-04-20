#ifndef FILEDATA_H
#define FILEDATA_H

#include <QString>

class FileData
{
public:
    FileData(qint64 size, QString type, QString name);
    FileData();

    qint64      size() const { return m_Size; }
    QString     type() const { return m_Type; }
    QString     name() const { return m_Name; }

private:
    qint64  m_Size;
    QString m_Type;
    QString m_Name;
};

#endif // FILEDATA_H
