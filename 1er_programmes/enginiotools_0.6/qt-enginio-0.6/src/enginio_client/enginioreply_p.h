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

#ifndef ENGINIOREPLY_P_H
#define ENGINIOREPLY_P_H

#include <QtCore/qhash.h>
#include <QtCore/qstring.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsondocument.h>
#include <QtNetwork/qnetworkreply.h>

#include "enginioclient_p.h"
#include "enginioreply.h"

class EnginioReplyPrivate {
public:
    EnginioClientPrivate *_client;
    QNetworkReply *_nreply;
    mutable QJsonObject _data;
    bool _delay;
    EnginioReplyPrivate(EnginioClientPrivate *p, QNetworkReply *reply)
        : _client(p)
        , _nreply(reply)
        , _delay(false)
    {
        Q_ASSERT(reply);
    }

    bool isFinished() const Q_REQUIRED_RESULT
    {
        return _nreply->isFinished() && Q_LIKELY(!_delay);
    }

    QNetworkReply::NetworkError errorCode() const Q_REQUIRED_RESULT
    {
        return _nreply->error();
    }

    int backendStatus() const Q_REQUIRED_RESULT
    {
        return _nreply->attribute(QNetworkRequest::HttpStatusCodeAttribute).value<int>();
    }

    QString requestId() const Q_REQUIRED_RESULT
    {
        return QString::fromUtf8(_nreply->request().rawHeader(EnginioString::XRequestId));
    }

    QString errorString() const Q_REQUIRED_RESULT
    {
        return _nreply->errorString();
    }

    EnginioReply::ErrorTypes errorType() const Q_REQUIRED_RESULT
    {
        if (errorCode() == QNetworkReply::NoError)
            return EnginioReply::NoError;
        if (data().isEmpty())
            return EnginioReply::NetworkError;
        return EnginioReply::BackendError;
    }

    QJsonObject data() const Q_REQUIRED_RESULT
    {
        if (_data.isEmpty())
            _data = QJsonDocument::fromJson(_nreply->readAll()).object();
        return _data;
    }

    void dumpDebugInfo() const
    {
        static QHash<QNetworkAccessManager::Operation, QByteArray> operationNames;
        operationNames[QNetworkAccessManager::GetOperation] = "GET";
        operationNames[QNetworkAccessManager::PutOperation] = "PUT";
        operationNames[QNetworkAccessManager::PostOperation] = "POST";
        operationNames[QNetworkAccessManager::DeleteOperation] = "DELETE";
        operationNames[QNetworkAccessManager::CustomOperation] = "CUSTOM";

        QNetworkRequest request = _nreply->request();
        qDebug() << "NetworkReply:" << _nreply;
        qDebug() << "  Request URL:" << request.url().toString(/*FormattingOptions*/ QUrl::None);
        qDebug() << "  Operation:" << operationNames[_nreply->operation()];
        qDebug() << "  HTTP return code:" << backendStatus();

        QByteArray json = _client->_requestData.value(_nreply);
        if (!json.isEmpty())
            qDebug() << "Request Data:" << json;

        if (!_data.isEmpty())
            qDebug() << "Reply Data:" << _data;
    }
};


#endif // ENGINIOREPLY_P_H
