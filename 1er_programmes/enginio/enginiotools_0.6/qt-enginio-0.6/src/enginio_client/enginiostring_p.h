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

#ifndef ENGINIOSTRING_P_H
#define ENGINIOSTRING_P_H

#include "enginioclient_global.h"
#include <QtCore/qstring.h>

#define FOR_EACH_ENGINIO_STRING(F)\
    F(_synced, "_synced")\
    F(_delete, "delete")\
    F(access, "access")\
    F(apiEnginIo, "https://api.engin.io")\
    F(apiRequestId, "apiRequestId")\
    F(authIdentity, "auth/identity")\
    F(complete, "complete")\
    F(count, "count")\
    F(create, "create")\
    F(createdAt, "createdAt")\
    F(data, "data")\
    F(empty, "empty")\
    F(event, "event")\
    F(expiringUrl, "expiringUrl")\
    F(file, "file")\
    F(fileName, "fileName")\
    F(files, "files")\
    F(headers, "headers")\
    F(id, "id")\
    F(include, "include")\
    F(incomplete, "incomplete")\
    F(limit, "limit")\
    F(members, "members")\
    F(message, "message")\
    F(messageType, "messageType")\
    F(object, "object")\
    F(objectType, "objectType")\
    F(objectTypes, "objectTypes")\
    F(offset, "offset")\
    F(origin, "origin")\
    F(pageSize, "pageSize")\
    F(password, "password")\
    F(payload, "payload")\
    F(propertyName, "propertyName")\
    F(query, "query")\
    F(results, "results")\
    F(search, "search")\
    F(session, "session")\
    F(sessionToken, "sessionToken")\
    F(sort, "sort")\
    F(stagingEnginIo, "https://staging.engin.io")\
    F(status, "status")\
    F(targetFileProperty, "targetFileProperty")\
    F(update, "update")\
    F(updatedAt, "updatedAt")\
    F(url, "url")\
    F(usergroups, "usergroups")\
    F(username, "username")\
    F(users, "users")\
    F(variant, "variant")\


struct ENGINIOCLIENT_EXPORT EnginioString
{
#define DECLARE_ENGINIO_STRING(Name, String)\
    static const QString Name;

    FOR_EACH_ENGINIO_STRING(DECLARE_ENGINIO_STRING)
#undef DECLARE_ENGINIO_STRING

    static const QByteArray XRequestId;
};


#endif // ENGINIOSTRING_P_H
