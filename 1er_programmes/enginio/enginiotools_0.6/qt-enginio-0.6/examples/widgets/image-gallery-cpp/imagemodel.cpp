#include "imagemodel.h"
#include "qabstractitemmodel.h"
#include <qjsonvalue.h>
#include <qjsonobject.h>
#include <qvariant.h>
#include <qicon.h>
#include <QtCore/qdatetime.h>

ImageModel::ImageModel(QObject *parent)
    : EnginioModel(parent)
{
    connect(this, SIGNAL(modelReset()),
            this, SLOT(reset()));
    connect(this, SIGNAL(rowsInserted(QModelIndex,int,int)),
            this, SLOT(updateRows(QModelIndex,int,int)));

    connect(this, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(onDataChanged(QModelIndex,QModelIndex)));
}

void ImageModel::reset()
{
    updateRows(QModelIndex(), 0, rowCount() - 1);
}

void ImageModel::updateRows(const QModelIndex &, int start, int end)
{
    for (int row = start; row <= end; ++row) {
        QJsonValue rowData = EnginioModel::data(index(row)).value<QJsonValue>();
        QString id = rowData.toObject().value("id").toString();
        if (id.isEmpty() || m_images.contains(id))
            continue;
        ImageObject *image = new ImageObject(enginio());
        connect(image, SIGNAL(imageChanged(QString)), this, SLOT(imageChanged(QString)));
        m_images.insert(id, image);
        image->setObject(rowData.toObject());
        QModelIndex changedIndex = index(row);
        emit dataChanged(changedIndex, changedIndex);
    }
}

void ImageModel::imageChanged(const QString &id)
{
    for (int row = 0; row < rowCount(); ++row) {
        if (data(index(row), Id) == id) {
            QModelIndex changedIndex = index(row);
            emit dataChanged(changedIndex, changedIndex);
        }
    }
}

void ImageModel::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    int start = topLeft.row();
    int end = bottomRight.row();

    updateRows(QModelIndex(), start, end);
}

QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.parent().isValid()
            || index.row() < 0 || index.row() >= rowCount())
        return QVariant();

    QJsonObject rowData = EnginioModel::data(index).value<QJsonValue>().toObject();

    switch (role) {
    case Id: {
        return rowData.value("id").toString();
    }
    case Qt::DecorationRole: {
        QString id = rowData.value("id").toString();
        if (m_images.contains(id))
            return m_images.value(id)->thumbnail();
        return QVariant();
    }
    case Qt::SizeHintRole: {
        return QVariant(QSize(100, 100));
    }
    case FileName:
        return rowData.value("file").toObject().value("fileName").toString();
    case FileSize:
        return QString::number(rowData.value("file").toObject().value("fileSize").toDouble());
    case CreationTime:
        return QDateTime::fromString(rowData.value("file").toObject().value("createdAt").toString(), Qt::ISODate);
    }

    return QVariant();
}

Qt::ItemFlags ImageModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsEnabled;
}
