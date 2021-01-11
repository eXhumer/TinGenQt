#include "googlefsitem.h"

GoogleFSItem::GoogleFSItem(const QVector<QMap<Qt::ItemDataRole, QVariant>> &itemData, GoogleFSItem *parent)
    : m_itemData(itemData), m_parentItem(parent)
{}

GoogleFSItem::~GoogleFSItem()
{
    qDeleteAll(this->m_childItems);
}

void GoogleFSItem::appendChild(GoogleFSItem *child)
{
    this->m_childItems.append(child);
}

GoogleFSItem *GoogleFSItem::child(int row) const
{
    if(row < 0 || row >= this->m_childItems.size())
        return nullptr;
    return this->m_childItems.at(row);
}

int GoogleFSItem::childCount() const
{
    return this->m_childItems.count();
}

int GoogleFSItem::columnCount() const
{
    return this->m_itemData.count();
}

QVariant GoogleFSItem::data(int column, Qt::ItemDataRole role) const
{
    return this->m_itemData.at(column)[role];
}

int GoogleFSItem::row() const
{
    if (this->m_parentItem)
        return this->m_parentItem->m_childItems.indexOf(const_cast<GoogleFSItem*>(this));

    return 0;
}

GoogleFSItem *GoogleFSItem::parentItem()
{
    return this->m_parentItem;
}
