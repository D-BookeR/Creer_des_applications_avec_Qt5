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

#ifndef ENGINIOFAKEREPLY_P_H
#define ENGINIOFAKEREPLY_P_H

#include "enginioclient_global.h"
#include "enginioreply.h"

#include <QtNetwork/qnetworkreply.h>
#include <QtCore/qbytearray.h>

class ENGINIOCLIENT_EXPORT EnginioFakeReply : public QNetworkReply
{
    Q_OBJECT
    QByteArray _msg;
public:
    explicit EnginioFakeReply(EnginioClientPrivate *parent, QByteArray msg);

    virtual void abort() Q_DECL_OVERRIDE;
    virtual bool isSequential() const Q_DECL_OVERRIDE;
    virtual qint64 size() const Q_DECL_OVERRIDE;
    virtual qint64 readData(char *dest, qint64 n) Q_DECL_OVERRIDE;
    virtual qint64 writeData(const char *data, qint64 maxSize) Q_DECL_OVERRIDE;
};

#endif // ENGINIOFAKEREPLY_P_H
