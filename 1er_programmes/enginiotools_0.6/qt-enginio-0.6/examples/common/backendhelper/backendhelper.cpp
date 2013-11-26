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

#include <Enginio/enginioclient.h>
#include <QtWidgets>
#include "backendhelper.h"
#include "ui_helperdialog.h"

const QString backendIdKey = QStringLiteral("backendId");
const QString backendSecretKey = QStringLiteral("backendSecret");
const QString showAgainKey = QStringLiteral("showAgain");

QPair<QByteArray, QByteArray> backendIdAndSecret(const QString &exampleName)
{
    QSettings *settings;

    QString fileName = QStringLiteral("EnginioExamples.conf");
    for (int i = 0; i < 4; ++i) {
        if (QFile::exists(fileName))
            break;
        fileName = fileName.prepend("../");
    }

    QFileInfo settingsFile = QFileInfo(fileName);

    if (settingsFile.exists()) {
        settings = new QSettings(settingsFile.absoluteFilePath(), QSettings::IniFormat);
    } else {
        settings = new QSettings("com.digia", "EnginioExamples");
    }

    settings->beginGroup(exampleName);
    QByteArray id = settings->value(backendIdKey).toByteArray();
    QByteArray secret= settings->value(backendSecretKey).toByteArray();
    bool askAgain = settings->value(showAgainKey, true).toBool();

    if (askAgain || id.isEmpty() || secret.isEmpty()) {
        Ui::Dialog dialog;
        QDialog d;
        dialog.setupUi(&d);
        dialog.backendId->setText(id);
        dialog.backendSecret->setText(secret);

        if (d.exec() == QDialog::Accepted) {
            id = dialog.backendId->text().toLocal8Bit();
            secret = dialog.backendSecret->text().toLocal8Bit();
            askAgain = !dialog.askAgain->isChecked();
            settings->setValue(backendIdKey, id);
            settings->setValue(backendSecretKey, secret);
            settings->setValue(showAgainKey, askAgain);
        }
    }

    settings->endGroup();
    settings->sync();
    delete settings;

    return qMakePair(id, secret);
}

