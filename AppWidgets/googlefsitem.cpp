/***************************************************************************
**
** TinGen - Index Generator for Tinfoil
** Copyright (C) 2021 eXhumer
**
** $QT_BEGIN_LICENSE:GPL3$
** GNU General Public License Usage
** This file may be used under the terms of the GNU General Public License
** version 3. The licenses are as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL3 included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License requirements will be met:
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
**
** $QT_END_LICENSE$
**
***************************************************************************/

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
