#ifndef TREEMODELITEM_H
#define TREEMODELITEM_H

#include <QVector>
#include <QVariant>

class TreeModelItem
{
public:
    explicit TreeModelItem(const QVector<QMap<int, QVariant>> &itemData, TreeModelItem *parentItem = nullptr);
    ~TreeModelItem();

    void appendChild(TreeModelItem *child);
    TreeModelItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column, int role = Qt::DisplayRole);
    int row() const;
    TreeModelItem *parentItem();

private:
    TreeModelItem *m_parentItem;
    QVector<QMap<int, QVariant>> m_itemData;
    QVector<TreeModelItem*> m_childItems;
};

#endif // TREEMODELITEM_H
