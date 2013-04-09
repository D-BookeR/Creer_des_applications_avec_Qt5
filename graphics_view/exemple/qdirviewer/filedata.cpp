#include "filedata.h"

FileData::FileData(qint64 size, QString type, QString name) :
    m_Size(size),
    m_Type(type),
    m_Name(name)
{}

FileData::FileData() :
    m_Size(0)
{}
