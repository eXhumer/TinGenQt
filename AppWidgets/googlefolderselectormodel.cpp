#include "googlefolderselectormodel.h"

GoogleFolderSelectorModel::GoogleFolderSelectorModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    QVector<QMap<int, QVariant>> itemData{
        {{Qt::DisplayRole, QString(tr("model.name"))}},
        {{Qt::DisplayRole, QString(tr("model.summary"))}}
    };
    this->rootItem = new GoogleFolderSelectorItem(itemData);
}

GoogleFolderSelectorModel::~GoogleFolderSelectorModel()
{
    delete this->rootItem;
}

QVariant GoogleFolderSelectorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
        return this->rootItem->data(section, (Qt::ItemDataRole)role);

    return QVariant();
}

Qt::ItemFlags GoogleFolderSelectorModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractTableModel::flags(index);
}

QModelIndex GoogleFolderSelectorModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!this->hasIndex(row, column, parent))
        return QModelIndex();

    GoogleFolderSelectorItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<GoogleFolderSelectorItem*>(parent.internalPointer());

    GoogleFolderSelectorItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex GoogleFolderSelectorModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    GoogleFolderSelectorItem *childItem = static_cast<GoogleFolderSelectorItem*>(index.internalPointer());
    GoogleFolderSelectorItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int GoogleFolderSelectorModel::rowCount(const QModelIndex &parent) const
{
    GoogleFolderSelectorItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<GoogleFolderSelectorItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int GoogleFolderSelectorModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<GoogleFolderSelectorItem*>(parent.internalPointer())->columnCount();

    return this->rootItem->columnCount();
}

bool GoogleFolderSelectorModel::hasChildren(const QModelIndex &parent) const
{
    return this->rowCount(parent) > 0;
}

bool GoogleFolderSelectorModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return false;
}

void GoogleFolderSelectorModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent);
    return;
}

QVariant GoogleFolderSelectorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    GoogleFolderSelectorItem *item = static_cast<GoogleFolderSelectorItem*>(index.internalPointer());

    return item->data(index.column(), (Qt::ItemDataRole)role);
}
