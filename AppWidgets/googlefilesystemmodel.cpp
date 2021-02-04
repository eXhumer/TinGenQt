#include "googlefilesystemmodel.h"
#include <QIcon>

GoogleFileSystemModel::GoogleFileSystemModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QMap<int, QVariant>> headerColumnDatas;
    QMap<int, QVariant> nameColumnData{
        {Qt::DisplayRole, "Name"},
    };
    QMap<int, QVariant> modifiedDateColumnData{
        {Qt::DisplayRole, "Modified Date"},
    };
    QMap<int, QVariant> fileSizeColumnData{
        {Qt::DisplayRole, "File Size"},
    };
    headerColumnDatas.push_back(nameColumnData);
    headerColumnDatas.push_back(modifiedDateColumnData);
    headerColumnDatas.push_back(fileSizeColumnData);
    this->rootItem = new TreeModelItem(headerColumnDatas, nullptr);
}

GoogleFileSystemModel::~GoogleFileSystemModel()
{
    delete this->rootItem;
}

QString GoogleFileSystemModel::fileID(const QModelIndex &index) const
{
    return this->data(index, GoogleFileSystemModel::FileIDRole).toString();
}

QString GoogleFileSystemModel::fileName(const QModelIndex &index) const
{
    return this->data(index, GoogleFileSystemModel::FileNameRole).toString();
}

GoogleFileSystemModel::FileType GoogleFileSystemModel::fileType(const QModelIndex &index) const
{
    return this->data(index, GoogleFileSystemModel::FileTypeRole).value<GoogleFileSystemModel::FileType>();
}

QIcon GoogleFileSystemModel::fileIcon(const QModelIndex &index) const
{
    return this->data(index, GoogleFileSystemModel::FileIconRole).value<QIcon>();
}

GoogleFileSystemModel::SelectState GoogleFileSystemModel::selectState(const QModelIndex &index) const
{
    return this->data(index, GoogleFileSystemModel::FileSelectedRole).value<GoogleFileSystemModel::SelectState>();
}

QVariant GoogleFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return this->rootItem->data(section, role);

    return QVariant();
}

QModelIndex GoogleFileSystemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (this->hasIndex(row, column, parent))
    {
        TreeModelItem *parentItem;

        if (!parent.isValid())
            parentItem = rootItem;
        else
            parentItem = static_cast<TreeModelItem*>(parent.internalPointer());

        TreeModelItem *childItem = parentItem->child(row);

        if (childItem)
            return this->createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex GoogleFileSystemModel::parent(const QModelIndex &index) const
{
    // TODO: FIXME
}

int GoogleFileSystemModel::rowCount(const QModelIndex &parent) const
{
    // TODO: FIXME
}

int GoogleFileSystemModel::columnCount(const QModelIndex &parent) const
{
    // TODO: FIXME
}

bool GoogleFileSystemModel::hasChildren(const QModelIndex &parent) const
{
    // TODO: FIXME
}

bool GoogleFileSystemModel::canFetchMore(const QModelIndex &parent) const
{
    // TODO: FIXME
}

void GoogleFileSystemModel::fetchMore(const QModelIndex &parent)
{
    // TODO: FIXME
}

QVariant GoogleFileSystemModel::data(const QModelIndex &index, int role) const
{
    // TODO: FIXME
}

Qt::ItemFlags GoogleFileSystemModel::flags(const QModelIndex &index) const
{
    // TODO: FIXME
}
