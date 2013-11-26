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

#ifndef ENGINIOQMLCLIENT_P_H
#define ENGINIOQMLCLIENT_P_H

#include <Enginio/private/enginioclient_p.h>

#include <QtQml/qjsengine.h>
#include <QtQml/qjsvalue.h>

class EnginioQmlClientPrivate : public EnginioClientPrivate
{
    QJSEngine *_engine;
    QJSValue _stringify;
    QJSValue _parse;
public:
    EnginioQmlClientPrivate(EnginioClient *client)
        : EnginioClientPrivate(client)
        , _engine(0)
    {}

    void init();

    inline void setEngine(const QJSValue &object)
    {
        if (Q_UNLIKELY(!_engine))
            _setEngine(object.engine());
    }

    QByteArray toJson(const QJSValue &value);
    QJSValue fromJson(const QByteArray &value);
private:
    void _setEngine(QJSEngine *engine);
};

#endif // ENGINIOQMLCLIENT_P_H
