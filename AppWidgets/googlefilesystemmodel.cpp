#include "googlefilesystemmodel.h"
#include <QIcon>

GoogleFileSystemModel::GoogleFileSystemModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    // TODO: FIXME
}

QString GoogleFileSystemModel::fileID(const QModelIndex &index) const
{
    // TODO: FIXME
}

QString GoogleFileSystemModel::fileName(const QModelIndex &index) const
{
    // TODO: FIXME
}

GoogleFileSystemModel::FileType GoogleFileSystemModel::fileType(const QModelIndex &index) const
{
    // TODO: FIXME
}

QIcon GoogleFileSystemModel::fileIcon(const QModelIndex &index) const
{
    // TODO: FIXME
}

bool GoogleFileSystemModel::isDir(const QModelIndex &index) const
{
    // TODO: FIXME
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
