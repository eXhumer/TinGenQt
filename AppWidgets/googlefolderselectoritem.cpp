#include "googlefolderselectoritem.h"

GoogleFolderSelectorItem::GoogleFolderSelectorItem(const QVector<QMap<int, QVariant>> &itemData, GoogleFolderSelectorItem *parent)
    : m_itemData(itemData), m_parentItem(parent)
{}

GoogleFolderSelectorItem::~GoogleFolderSelectorItem()
{
    qDeleteAll(this->m_childItems);
}

void GoogleFolderSelectorItem::appendChild(GoogleFolderSelectorItem *child)
{
    this->m_childItems.append(child);
}

GoogleFolderSelectorItem *GoogleFolderSelectorItem::child(int row) const
{
    if(row < 0 || row >= this->m_childItems.size())
        return nullptr;
    return this->m_childItems.at(row);
}

int GoogleFolderSelectorItem::childCount() const
{
    return this->m_childItems.count();
}

int GoogleFolderSelectorItem::columnCount() const
{
    return this->m_itemData.count();
}

QVariant GoogleFolderSelectorItem::data(int column, int role) const
{
    // TODO FIX
    return this->m_itemData.at(column)[(Qt::ItemDataRole)role];
}

int GoogleFolderSelectorItem::row() const
{
    if (this->m_parentItem)
        return this->m_parentItem->m_childItems.indexOf(const_cast<GoogleFolderSelectorItem*>(this));

    return 0;
}

GoogleFolderSelectorItem *GoogleFolderSelectorItem::parentItem()
{
    return this->m_parentItem;
}
