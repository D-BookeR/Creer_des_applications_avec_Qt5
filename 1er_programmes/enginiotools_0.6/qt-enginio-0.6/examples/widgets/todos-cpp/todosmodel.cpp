#include "todosmodel.h"

#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtGui/qcolor.h>
#include <QtGui/qfont.h>

#include <Enginio/enginioreply.h>

//![resetRoles]
TodosModel::TodosModel(QObject *parent)
    : EnginioModel(parent)
    , TitleRole()
    , CompletedRole()
{
    QObject::connect(this, &EnginioModel::modelReset, this, &TodosModel::updateRoles);
}
//![resetRoles]

QVariant TodosModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && section == 0 && role == Qt::DisplayRole)
        return QStringLiteral("Todo List");
    return EnginioModel::headerData(section, orientation, role);
}

//![data]
QVariant TodosModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return EnginioModel::data(index, TitleRole).value<QJsonValue>().toString();

    if (role == Qt::FontRole) {
        bool completed = EnginioModel::data(index, CompletedRole).value<QJsonValue>().toBool();
        QFont font;
        font.setPointSize(20);
        font.setStrikeOut(completed);
        return font;
    }

    if (role == Qt::TextColorRole) {
        bool completed = EnginioModel::data(index, CompletedRole).value<QJsonValue>().toBool();
        return completed ? QColor("#999") : QColor("#333");
    }

    if (role == CompletedRole)
        return EnginioModel::data(index, CompletedRole).value<QJsonValue>().toBool();

    if (role == TitleRole)
        return EnginioModel::data(index, TitleRole).value<QJsonValue>().toString();

    // fallback to base class
    return EnginioModel::data(index, role);
}
//![data]
//![setData]
bool TodosModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        EnginioReply *reply = setProperty(index.row(), "title", value);
        QObject::connect(reply, &EnginioReply::finished, reply, &EnginioReply::deleteLater);
        return true;
    }
    return false;
}
//![setData]

//![updateRoles]
void TodosModel::updateRoles()
{
    static QByteArray titleRoleName = QByteArrayLiteral("title");
    static QByteArray doneRoleName = QByteArrayLiteral("completed");
    QHash<int, QByteArray> roleNames = EnginioModel::roleNames();
    foreach(int role, roleNames.keys()) {
        QByteArray roleName = roleNames.value(role);
        if (roleName == titleRoleName) {
            TitleRole = role;
        } else if (roleName == doneRoleName) {
            CompletedRole = role;
        }
    }
}
//![updateRoles]

