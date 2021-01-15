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
