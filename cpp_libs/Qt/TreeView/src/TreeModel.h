#ifndef TREEMODEL_H
#define TREEMODEL_H

////////////////////////////////////////////////////////////////////////////////

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "TreeItem.h"

////////////////////////////////////////////////////////////////////////////////

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:

    explicit TreeModel(QObject *parent = nullptr);

    ~TreeModel();

private:

    TreeItem* root_ = nullptr;
};

////////////////////////////////////////////////////////////////////////////////

#endif // TREEMODEL_H
