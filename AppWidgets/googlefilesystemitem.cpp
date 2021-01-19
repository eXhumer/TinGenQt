#include "googlefilesystemitem.h"

GoogleFileSystemItem::GoogleFileSystemItem(const QVector<QMap<int, QVariant>> &itemData, GoogleFileSystemItem *parentItem)
    : m_parentItem(parentItem), m_itemData(itemData)
{}

GoogleFileSystemItem::~GoogleFileSystemItem()
{
    qDeleteAll(this->m_childItems);
}

void GoogleFileSystemItem::appendChild(GoogleFileSystemItem *child)
{
    this->m_childItems.append(child);
}

GoogleFileSystemItem *GoogleFileSystemItem::child(int row)
{
    if(row < 0 || row >= this->m_childItems.size())
        return nullptr;
    return this->m_childItems.at(row);
}

int GoogleFileSystemItem::childCount() const
{
    return this->m_childItems.count();
}

int GoogleFileSystemItem::columnCount() const
{
    return this->m_itemData.count();
}

QVariant GoogleFileSystemItem::data(int column, int role)
{
    if (column < 0 || column >= this->m_itemData.size())
        return QVariant();
    return this->m_itemData.at(column)[role];
}

int GoogleFileSystemItem::row() const
{
    if(this->m_parentItem)
        return this->m_parentItem->m_childItems.indexOf(const_cast<GoogleFileSystemItem*>(this));

    return 0;
}

GoogleFileSystemItem *GoogleFileSystemItem::parentItem()
{
    return this->m_parentItem;
}
