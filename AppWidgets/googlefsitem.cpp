#include "googlefsitem.h"

GoogleFSItem::GoogleFSItem(const QVector<QMap<Qt::ItemDataRole, QVariant>> &itemData, GoogleFSItem *parent)
    : m_itemData(itemData), m_parentItem(parent)
{

}

GoogleFSItem::~GoogleFSItem()
{

}

void GoogleFSItem::appendChild(GoogleFSItem *child)
{

}

GoogleFSItem *GoogleFSItem::child(int row)
{

}

int GoogleFSItem::childCount() const
{

}

int GoogleFSItem::columnCount() const
{

}

QVariant GoogleFSItem::data(int column) const
{

}

int GoogleFSItem::row() const
{

}

GoogleFSItem *GoogleFSItem::parentItem()
{

}
