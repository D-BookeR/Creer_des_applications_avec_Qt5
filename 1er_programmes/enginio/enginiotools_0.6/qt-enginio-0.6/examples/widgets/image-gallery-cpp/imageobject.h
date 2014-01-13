#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <QtCore>
#include <QtGui>

class QNetworkReply;
class EnginioClient;
class EnginioReply;
class ImageObject : public QObject
{
    Q_OBJECT
public:
    explicit ImageObject(EnginioClient *enginio);

    void setObject(const QJsonObject &object);

    QImage image() { return m_image; }
    QPixmap thumbnail();

signals:
    void imageChanged(const QString &id);

private slots:
    void replyFinished(EnginioReply *enginioReply);
    void downloadFinished();

private:
    QImage m_image;
    QPixmap m_thumbnail;
    QNetworkReply *m_reply;
    EnginioClient *m_enginio;
    QJsonObject m_object;
};

#endif // IMAGEOBJECT_H
