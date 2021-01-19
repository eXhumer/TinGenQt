#ifndef GOOGLEFILESYSTEMITEM_H
#define GOOGLEFILESYSTEMITEM_H

#include <QVector>
#include <QVariant>

class GoogleFileSystemItem
{
public:
    explicit GoogleFileSystemItem(const QVector<QMap<int, QVariant>> &itemData, GoogleFileSystemItem *parentItem = nullptr);
    ~GoogleFileSystemItem();

    void appendChild(GoogleFileSystemItem *child);
    GoogleFileSystemItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column, int role = Qt::DisplayRole);
    int row() const;
    GoogleFileSystemItem *parentItem();

private:
    GoogleFileSystemItem *m_parentItem;
    QVector<QMap<int, QVariant>> m_itemData;
    QVector<GoogleFileSystemItem*> m_childItems;
};

#endif // GOOGLEFILESYSTEMITEM_H
