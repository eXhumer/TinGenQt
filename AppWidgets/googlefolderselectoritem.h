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

#ifndef GOOGLEFOLDERSELECTORITEM_H
#define GOOGLEFOLDERSELECTORITEM_H

#include <QVariant>
#include <QVector>

class GoogleFolderSelectorItem
{
public:
    GoogleFolderSelectorItem(const QVector<QMap<int, QVariant>> &itemData, GoogleFolderSelectorItem *parent = nullptr);
    ~GoogleFolderSelectorItem();

    void appendChild(GoogleFolderSelectorItem *child);
    GoogleFolderSelectorItem *child(int row) const;
    int childCount() const;
    int columnCount() const;
    QVariant data(int column, int dataRole) const;
    int row() const;
    GoogleFolderSelectorItem *parentItem();

private:
    QVector<QMap<int, QVariant>> m_itemData;
    QVector<GoogleFolderSelectorItem*> m_childItems;
    GoogleFolderSelectorItem *m_parentItem;
};

#endif // GOOGLEFOLDERSELECTORITEM_H
