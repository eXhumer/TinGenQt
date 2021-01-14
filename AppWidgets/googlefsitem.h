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

#ifndef GOOGLEFSITEM_H
#define GOOGLEFSITEM_H

#include <QVariant>
#include <QVector>

enum class GoogleFSItemDataRoles {
    FileIdRole = 0xcc,
    FileTypeRole = 0xdd,
};

class GoogleFSItem
{

public:
    GoogleFSItem(const QVector<QMap<int, QVariant>> &itemData, GoogleFSItem *parent = nullptr);
    ~GoogleFSItem();

    void appendChild(GoogleFSItem *child);
    GoogleFSItem *child(int row) const;
    int childCount() const;
    int columnCount() const;
    QVariant data(int column, int dataRole) const;
    int row() const;
    GoogleFSItem *parentItem();

private:
    QVector<QMap<int, QVariant>> m_itemData;
    QVector<GoogleFSItem*> m_childItems;
    GoogleFSItem *m_parentItem;
};

#endif // GOOGLEFSITEM_H
