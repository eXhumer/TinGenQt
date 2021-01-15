#ifndef GOOGLEFOLDERSELECTORMODEL_H
#define GOOGLEFOLDERSELECTORMODEL_H

#include "googlefolderselectoritem.h"
#include <QAbstractTableModel>

class GoogleFolderSelectorModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit GoogleFolderSelectorModel(QObject *parent = nullptr);
    ~GoogleFolderSelectorModel();

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    GoogleFolderSelectorItem *rootItem;
};

#endif // GOOGLEFOLDERSELECTORMODEL_H
