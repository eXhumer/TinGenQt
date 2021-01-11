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
