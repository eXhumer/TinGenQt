#include "treemodelitem.h"

TreeModelItem::TreeModelItem(const QVector<QMap<int, QVariant>> &itemData, TreeModelItem *parentItem)
    : m_parentItem(parentItem), m_itemData(itemData)
{}

TreeModelItem::~TreeModelItem()
{
    qDeleteAll(this->m_childItems);
}

void TreeModelItem::appendChild(TreeModelItem *child)
{
    this->m_childItems.append(child);
}

TreeModelItem *TreeModelItem::child(int row)
{
    if(row < 0 || row >= this->m_childItems.size())
        return nullptr;
    return this->m_childItems.at(row);
}

int TreeModelItem::childCount() const
{
    return this->m_childItems.count();
}

int TreeModelItem::columnCount() const
{
    return this->m_itemData.count();
}

QVariant TreeModelItem::data(int column, int role)
{
    if (column < 0 || column >= this->m_itemData.size())
        return QVariant();
    return this->m_itemData.at(column)[role];
}

int TreeModelItem::row() const
{
    if(this->m_parentItem)
        return this->m_parentItem->m_childItems.indexOf(const_cast<TreeModelItem*>(this));

    return 0;
}

TreeModelItem *TreeModelItem::parentItem()
{
    return this->m_parentItem;
}
