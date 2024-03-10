#include "TreeModel.h"

////////////////////////////////////////////////////////////////////////////////

TreeModel::TreeModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    root_ = new TreeItem({tr("Parameter"), tr("Value")});
}

////////////////////////////////////////////////////////////////////////////////

TreeModel::~TreeModel()
{
    if ( root_ ) { delete root_; } root_ = nullptr;
}
