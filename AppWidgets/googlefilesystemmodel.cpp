#include "googlefilesystemmodel.h"
#include <QIcon>

GoogleFileSystemModel::GoogleFileSystemModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    this->rootItem = new GoogleFileSystemItem({
        {{Qt::DisplayRole, "Test 1"}},
        {{Qt::DisplayRole, "Test 2"}},
    }, nullptr);
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

bool GoogleFileSystemModel::isDir(const QModelIndex &index) const
{
    return this->fileType(index) == GoogleFileSystemModel::Folder || this->fileType(index) == GoogleFileSystemModel::Drive;
}

GoogleFileSystemModel::SelectState GoogleFileSystemModel::selectState(const QModelIndex &index) const
{
    // TODO: FIXME
}

QVariant GoogleFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // TODO: FIXME
}

QModelIndex GoogleFileSystemModel::index(int row, int column, const QModelIndex &parent) const
{
    // TODO: FIXME
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
