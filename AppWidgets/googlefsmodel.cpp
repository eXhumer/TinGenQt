#include "googlefsmodel.h"

GoogleFSModel::GoogleFSModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QMap<Qt::ItemDataRole, QVariant>> itemData{
        {{Qt::DisplayRole, QString(tr("model.title"))}},
        {{Qt::DisplayRole, QString(tr("model.summary"))}}
    };
    this->rootItem = new GoogleFSItem(itemData);
}

GoogleFSModel::~GoogleFSModel()
{
    delete this->rootItem;
}

QVariant GoogleFSModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
        return this->rootItem->data(section, (Qt::ItemDataRole)role);

    return QVariant();
}

Qt::ItemFlags GoogleFSModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QModelIndex GoogleFSModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!this->hasIndex(row, column, parent))
        return QModelIndex();

    GoogleFSItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<GoogleFSItem*>(parent.internalPointer());

    GoogleFSItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex GoogleFSModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    GoogleFSItem *childItem = static_cast<GoogleFSItem*>(index.internalPointer());
    GoogleFSItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int GoogleFSModel::rowCount(const QModelIndex &parent) const
{
    GoogleFSItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<GoogleFSItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int GoogleFSModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<GoogleFSItem*>(parent.internalPointer())->columnCount();

    return this->rootItem->columnCount();
}

bool GoogleFSModel::hasChildren(const QModelIndex &parent) const
{
    return this->rowCount(parent) > 0;
}

bool GoogleFSModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return false;
}

void GoogleFSModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent);
    return;
}

QVariant GoogleFSModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    GoogleFSItem *item = static_cast<GoogleFSItem*>(index.internalPointer());

    return item->data(index.column(), (Qt::ItemDataRole)role);
}
