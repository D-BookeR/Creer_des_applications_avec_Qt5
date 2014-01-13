
#include "imageobject.h"

#include <QtNetwork>
#include <Enginio/enginioclient.h>
#include <Enginio/enginioreply.h>

ImageObject::ImageObject(EnginioClient *enginio)
    : m_enginio(enginio)
{}

void ImageObject::setObject(const QJsonObject &object)
{
    m_object = object;
    QString fileId;
    fileId = object.value("file").toObject().value("id").toString();

    if (!fileId.isEmpty()) {
        QJsonObject fileObject;
        fileObject.insert("id", fileId);
        fileObject.insert("variant", QString("thumbnail"));
        EnginioReply *reply = m_enginio->downloadFile(fileObject);
        connect(reply, SIGNAL(finished(EnginioReply*)), this, SLOT(replyFinished(EnginioReply*)));
    } else {
        // Try to fall back to the local file
        QString localPath = object.value("localPath").toString();
        if (QFile::exists(localPath)) {
            m_image = QImage(localPath);
            emit imageChanged(object.value("id").toString());
        }
    }
}

void ImageObject::replyFinished(EnginioReply *enginioReply)
{
    QString url = enginioReply->data().value("expiringUrl").toString();
    QNetworkRequest request(url);
    m_reply = m_enginio->networkManager()->get(request);
    m_reply->setParent(this);
    connect(m_reply, SIGNAL(finished()), this, SLOT(downloadFinished()));
}

void ImageObject::downloadFinished()
{
    QByteArray imageData = m_reply->readAll();
    m_image.loadFromData(imageData);
    emit imageChanged(m_object.value("id").toString());

    m_reply->deleteLater();
    m_reply = 0;
}

QPixmap ImageObject::thumbnail()
{
    if (m_image.isNull() || !m_thumbnail.size().isNull())
        return m_thumbnail;
    m_thumbnail = QPixmap::fromImage(m_image.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    return m_thumbnail;
}
