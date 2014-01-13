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

#ifndef ENGINIOQMLOBJECTADAPTOR_P_H
#define ENGINIOQMLOBJECTADAPTOR_P_H

#include "enginioqmlclient_p.h"

#include <Enginio/private/enginioobjectadaptor_p.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qstring.h>
#include <QtQml/qjsengine.h>
#include <QtQml/qjsvalue.h>
#include <QtQml/qjsvalueiterator.h>

template <> struct ValueAdaptor<QJSValue>;
template <> struct ObjectAdaptor<QJSValue>;
template <> struct ArrayAdaptor<QJSValue>;

template <> struct ValueAdaptor<QJSValue>
{
    QJSValue _value;
    EnginioQmlClientPrivate *_client;

    ValueAdaptor(const QJSValue &value, EnginioQmlClientPrivate *client)
        : _value(value)
        , _client(client)
    {}

    bool isComposedType() const { return _value.isObject(); }

    int toInt() const { return _value.toInt(); }
    QString toString() const { return _value.toString(); }
    ValueAdaptor<QJSValue> operator[](const QString &index) const
    {
        return ValueAdaptor<QJSValue>(_value.property(index), _client);
    }

    bool contains(const QString &key) const { return _value.hasProperty(key); }

    QByteArray toJson() const
    {
        return _client->toJson(_value);
    }
    void remove(const QString &index) { _value.deleteProperty(index); }

    ObjectAdaptor<QJSValue> toObject() const;
    ArrayAdaptor<QJSValue> toArray() const;
};

template <> struct ObjectAdaptor<QJSValue> : public ValueAdaptor<QJSValue>
{
    ObjectAdaptor(const QJSValue &value, EnginioQmlClientPrivate *client)
        : ValueAdaptor(value, client)
    {}
};

template <> struct ArrayAdaptor<QJSValue> : public ValueAdaptor<QJSValue>
{
    ArrayAdaptor(const QJSValue &value, EnginioQmlClientPrivate *client)
        : ValueAdaptor(value, client)
    {}

    ArrayAdaptor(const ArrayAdaptor<QJSValue> &value)
        : ValueAdaptor(value)
    {}

    struct const_iterator
    {
        QJSValueIterator _iter;
        QJSValue _value;

        const_iterator(const QJSValue &value = QJSValue())
            : _iter(value)
            , _value(value)
        {}

        const_iterator(const const_iterator &other)
            : _iter(other._value)
            , _value(other._value)
        {}

        bool operator !=(const const_iterator &other) const
        {
            return !other._iter.hasNext() && !_iter.hasNext();
        }
        QJSValue operator *()
        {
            return _iter.value();
        }
        void operator ++() { _iter.next(); }
    };

    const_iterator constBegin() const { return _value; }
    const_iterator constEnd() const { return const_iterator(); }
};

ObjectAdaptor<QJSValue> ValueAdaptor<QJSValue>::toObject() const { return ObjectAdaptor<QJSValue>(_value, _client); }
ArrayAdaptor<QJSValue> ValueAdaptor<QJSValue>::toArray() const { return ArrayAdaptor<QJSValue>(_value, _client); }


#endif // ENGINIOQMLOBJECTADAPTOR_P_H
