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
