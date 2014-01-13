#ifndef TODOSMODEL_H
#define TODOSMODEL_H

#include <Enginio/enginiomodel.h>

//![definition]
class TodosModel : public EnginioModel
{
    Q_OBJECT

public:
    int TitleRole;
    int CompletedRole;
//![definition]

    explicit TodosModel(QObject *parent = 0);
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

protected slots:
    void updateRoles();
};

#endif // TODOSMODEL_H
