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

#include "enginioqmlmodel.h"

/*!
  \qmltype EnginioModel
  \instantiates EnginioQmlModel
  \inqmlmodule Enginio 1
  \ingroup engino-qml

  \brief Makes accessing collections of objects easy
  \snippet simple.qml import

  The query property of the model takes a JSON object.

  To get a model of each object of type "objects.city" use:
  \snippet models.qml model

  It is then possible to use a regular Qt Quick ListView
  to display the list of cities that the backend contains.
  \snippet models.qml view
  Note that the properties of the objects can be directly accessed.
  In this example, we have the type "objects.city" in the backend
  with two properties: "name" and "population".

  The model supports several function to modify the data, for example
  \l append(), \l remove(), \l setProperty()

  The QML version of EnginioModel supports the same functionality as the C++ version.
  \l {EnginioModelCpp}{EnginioModel C++}
*/

/*!
  \qmlproperty QJsonObject Enginio1::EnginioModel::query
  The query used to populate the model with data.
*/

/*!
  \qmlproperty Enginio Enginio1::EnginioModel::enginio
  The instance of \l Enginio used for this model.
*/

/*!
  \qmlproperty EnginioClient::Operation Enginio1::EnginioModel::operation
  The operation used for the \l query.
*/

/*!
  \qmlmethod EnginioReply Enginio1::EnginioModel::append(QJsonObject value)
  \brief Add a new object to the model and database.

  To add a "city" object to the model by appending it:
  \snippet models.qml append
  The append will be reflected by the model immediately and will be propagated
  to the server asynchronously.

  The returned \l Enginio1::EnginioReply can be used to react to a finished object creation.
*/

/*!
  \qmlmethod EnginioReply Enginio1::EnginioModel::setProperty(int row, string propertyName, QVariant value)
  \brief Change a property of an object in the model

  The property \a propertyName of the object at \a row will be set to \a value.
  The model will locally reflect the change immediately and propagage the change to the
  server in the background.
*/

/*!
  \qmlmethod EnginioReply Enginio1::EnginioModel::remove(int row)
  \brief removes the object at \a row
*/

EnginioQmlModel::EnginioQmlModel(QObject *parent)
    : EnginioModel(parent)
{
}
