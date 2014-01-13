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

#ifndef ENGINIOREPLY_H
#define ENGINIOREPLY_H

#include <QtCore/qobject.h>
#include <QtCore/qscopedpointer.h>
#include <QtCore/qstring.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qtypeinfo.h>
#include <QtCore/qmetatype.h>
#include <QtNetwork/qnetworkreply.h>

#include "enginioclient_global.h"

class EnginioClient;
class EnginioReplyPrivate;
class EnginioClientPrivate;

class ENGINIOCLIENT_EXPORT EnginioReply : public QObject
{
    Q_OBJECT
public:
    enum ErrorTypes {
        NoError,
        NetworkError,
        BackendError
    };
    Q_ENUMS(ErrorTypes)

    Q_PROPERTY(QJsonObject data READ data NOTIFY dataChanged)
    Q_PROPERTY(ErrorTypes errorType READ errorType NOTIFY errorChanged)
    Q_PROPERTY(QNetworkReply::NetworkError networkError READ networkError NOTIFY errorChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY errorChanged)
    Q_PROPERTY(int backendStatus READ backendStatus NOTIFY finished)
    Q_PROPERTY(QString requestId READ requestId CONSTANT)

    explicit EnginioReply(EnginioClientPrivate *parent, QNetworkReply *reply);
    virtual ~EnginioReply();

    QJsonObject data() const Q_REQUIRED_RESULT;
    ErrorTypes errorType() const Q_REQUIRED_RESULT;
    QNetworkReply::NetworkError networkError() const Q_REQUIRED_RESULT;
    QString errorString() const Q_REQUIRED_RESULT;
    QString requestId() const Q_REQUIRED_RESULT;
    int backendStatus() const Q_REQUIRED_RESULT;

    bool isError() const Q_REQUIRED_RESULT;
    bool isFinished() const Q_REQUIRED_RESULT;

    Q_SLOT void dumpDebugInfo() const;

    void setDelayFinishedSignal(bool delay);
    bool delayFinishedSignal() Q_REQUIRED_RESULT;
    void setNetworkReply(QNetworkReply *reply);
    void swapNetworkReply(EnginioReply *reply);
Q_SIGNALS:
    void finished(EnginioReply *reply);
    void dataChanged();
    void errorChanged();
    void progress(qint64 bytesSent, qint64 bytesTotal);

protected:
    explicit EnginioReply(EnginioClientPrivate *parent, QNetworkReply *reply, EnginioReplyPrivate *priv);
    virtual void emitFinished();
    QScopedPointer<EnginioReplyPrivate> d;

private:
    Q_DISABLE_COPY(EnginioReply)

    friend class EnginioClient;
    friend class EnginioClientPrivate;
};

Q_DECLARE_TYPEINFO(const EnginioReply*, Q_PRIMITIVE_TYPE);
Q_DECLARE_METATYPE(const EnginioReply*);
Q_DECLARE_TYPEINFO(EnginioReply::ErrorTypes, Q_PRIMITIVE_TYPE);
Q_DECLARE_METATYPE(EnginioReply::ErrorTypes)

#ifndef QT_NO_DEBUG_STREAM
ENGINIOCLIENT_EXPORT QDebug operator<<(QDebug d, const EnginioReply *reply);
#endif


#endif // ENGINIOREPLY_H
