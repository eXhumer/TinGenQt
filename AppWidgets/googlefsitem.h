/*
    TinGen - Index Generator for Tinfoil
    Copyright (C) 2021 eXhumer

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef GOOGLEFSITEM_H
#define GOOGLEFSITEM_H

#include <QVariant>
#include <QVector>

class GoogleFSItem
{

public:
    GoogleFSItem(const QVector<QMap<Qt::ItemDataRole, QVariant>> &itemData, GoogleFSItem *parent = nullptr);
    ~GoogleFSItem();

    void appendChild(GoogleFSItem *child);
    GoogleFSItem *child(int row) const;
    int childCount() const;
    int columnCount() const;
    QVariant data(int column, Qt::ItemDataRole dataRole) const;
    int row() const;
    GoogleFSItem *parentItem();

private:
    QVector<QMap<Qt::ItemDataRole, QVariant>> m_itemData;
    QVector<GoogleFSItem*> m_childItems;
    GoogleFSItem *m_parentItem;
};

#endif // GOOGLEFSITEM_H
