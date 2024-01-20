#ifndef TREEITEM_H
#define TREEITEM_H

////////////////////////////////////////////////////////////////////////////////

#include <QVariant>
#include <QVector>

////////////////////////////////////////////////////////////////////////////////


class TreeItem
{
public:

    TreeItem(const QVector<QVariant>& data, TreeItem* parent = nullptr);

    ~TreeItem();

    void appendChild(TreeItem* item);

    TreeItem* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem* parent();

private:

    TreeItem* parent_ = nullptr;
    QVector<TreeItem*> children_;

    QVector<QVariant> data_;
};

////////////////////////////////////////////////////////////////////////////////

#endif // TREEITEM_H
