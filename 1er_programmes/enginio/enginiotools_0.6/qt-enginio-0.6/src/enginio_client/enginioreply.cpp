/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://qt.digia.com/contact-us
**
** This file is part of the Enginio Qt Client Library.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#include <QtCore/qstring.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsondocument.h>
#include <QtNetwork/qnetworkreply.h>

#include "enginioreply.h"
#include "enginioreply_p.h"
#include "enginioclient.h"
#include "enginioclient_p.h"
#include "enginioobjectadaptor_p.h"

/*!
  \class EnginioReply
  \brief The EnginioReply class contains the data from a request to the Enginio database.
  \inmodule enginio-qt
  \ingroup enginio-client

  The finished signal is emitted when the query is done.

  \sa EnginioClient
*/

/*!
  \enum EnginioReply::ErrorTypes
  Describes the type of error that occured when making a request to the Enginio backend.
  \value NoError The reply returned without errors
  \value NetworkError The error was a networking problem
  \value BackendError The backend did not accept the query
*/

/*!
  \fn EnginioReply::finished(EnginioReply *reply)
  This signal is emitted when the EnginioReply \a reply is finished.
  After the network operation, use the \l isError() function to check for
  potential problems and then use the \l data property to access the returned data.
*/

/*!
  \fn EnginioReply::progress(qint64 bytesSent, qint64 bytesTotal)
  This signal is emitted for file operations, indicating the progress of up or downloads.
  The \a bytesSent is the current progress relative to the total \a bytesTotal.
*/

/*!
  \internal
*/
EnginioReply::EnginioReply(EnginioClientPrivate *p, QNetworkReply *reply)
    : QObject(p->q_ptr)
    , d(new EnginioReplyPrivate(p, reply))
{
    p->registerReply(reply, this);
}

/*!
  \internal
*/
EnginioReply::EnginioReply(EnginioClientPrivate *parent, QNetworkReply *reply, EnginioReplyPrivate *priv)
    : QObject(parent->q_ptr)
    , d(priv)
{
    parent->registerReply(reply, this);
}


/*!
  \brief Destroys the EnginioReply.

  The reply needs to be deleted after the finished signal is emitted.
*/
EnginioReply::~EnginioReply()
{
    // At this point d pointer may be null, because it may be deleted by
    // EnginioQmlReply. If you need to add code here, then consider to
    // make EnginioReply destructor virtual. For now there is no point
    // in adding vtable to the private class.
}

/*!
  \property EnginioReply::networkError
  This property holds the network error for the request.
*/
QNetworkReply::NetworkError EnginioReply::networkError() const
{
    return d->errorCode();
}

/*!
  \property EnginioReply::errorString
  This property holds the error for the request as human readable string.
  Check \l isError() first to check if the reply is an error.
*/
QString EnginioReply::errorString() const
{
    return d->errorString();
}

/*!
  \property EnginioReply::requestId
  This property holds the API request ID for the request.
  The request ID is useful for end-to-end tracking of requests and to identify
  the origin of notifications.
  \internal
*/

/*!
  \internal
*/
QString EnginioReply::requestId() const
{
    return d->requestId();
}

/*!
  \property EnginioReply::data
  \brief The data returned from the backend
  This property holds the JSON data returned by the server after a successful request.
*/

QJsonObject EnginioReply::data() const
{
    return d->data();
}

/*!
  \internal
*/
void EnginioReply::emitFinished()
{
    emit finished(this);
}

/*!
  \internal
*/
void EnginioReply::setNetworkReply(QNetworkReply *reply)
{
    d->_client->_replyReplyMap.remove(d->_nreply);

    if (gEnableEnginioDebugInfo)
        d->_client->_requestData.remove(d->_nreply);

    d->_nreply->deleteLater();
    d->_nreply = reply;
    d->_data = QJsonObject();
    d->_client->registerReply(reply, this);
}

/*!
  \internal
*/
void EnginioReply::swapNetworkReply(EnginioReply *reply)
{
    // FIXME it is ugly
    d->_client->_replyReplyMap.remove(d->_nreply);
    reply->d->_client->_replyReplyMap.remove(reply->d->_nreply);

    qSwap(d->_nreply, reply->d->_nreply);

    d->_data = reply->d->_data = QJsonObject();

    d->_client->registerReply(d->_nreply, this);
    reply->d->_client->registerReply(reply->d->_nreply, reply);
}

void EnginioReply::dumpDebugInfo() const
{
    d->dumpDebugInfo();
}

/*!
  \internal
  Mark this EnginioReply as not finished, the finished signal
  will be delayed until delayFinishedSignal() is returning true.

  \note The feature can be used only with one EnginioClient
*/
void EnginioReply::setDelayFinishedSignal(bool delay)
{
    d->_delay = delay;
    d->_client->finishDelayedReplies();
}

/*!
  \internal
  Returns true if signal should be delayed
 */
bool EnginioReply::delayFinishedSignal()
{
    return d->_delay;
}

/*!
  \brief EnginioReply::isError returns whether this reply was unsuccessful
  \return true if the reply did not succeed
*/
bool EnginioReply::isError() const
{
    return d->errorCode() != QNetworkReply::NoError;
}

/*!
  \brief EnginioReply::isFinished returns whether this reply was finished or not
  \return true if the reply was finished, false otherwise.
*/
bool EnginioReply::isFinished() const
{
    return d->isFinished();
}

/*!
  \property EnginioReply::backendStatus
  \return the backend return status for this reply.
  \sa EnginioReply::ErrorTypes
*/
int EnginioReply::backendStatus() const
{
    return d->backendStatus();
}

/*!
  \property EnginioReply::errorType
  \return the type of the error
  \sa EnginioReply::ErrorTypes
*/
EnginioReply::ErrorTypes EnginioReply::errorType() const
{
    return d->errorType();
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const EnginioReply *reply)
{
    if (!reply) {
        d << "EnginioReply(null)";
        return d;
    }
    d.nospace();
    d << "EnginioReply(" << hex << (void *) reply << dec;

    if (!reply->isError()) {
        d << " success data=" << reply->data();
    } else {
        d << " errorCode=" << reply->networkError() << " ";
        d << " errorString=" << reply->errorString() << " ";
        d << " errorData=" << reply->data() << " ";
    }
    d << "backendStatus=" << reply->backendStatus();
    d << ")";
    return d.space();
}
#endif // QT_NO_DEBUG_STREAM
