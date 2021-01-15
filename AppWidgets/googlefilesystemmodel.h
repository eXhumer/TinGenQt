#ifndef GOOGLEFILESYSTEMMODEL_H
#define GOOGLEFILESYSTEMMODEL_H

#include <QAbstractItemModel>

class GoogleFileSystemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum FileType {
        Drive,
        File,
        Folder,
        Shortcut,
    };

    enum Roles {
        FileIDRole = Qt::UserRole + 1,
        FileTypeRole = Qt::UserRole + 2,
        FileNameRole = Qt::DisplayRole,
        FileSelectedRole = Qt::CheckStateRole,
        FileIconRole = Qt::DecorationRole,
    };

    QString fileID(const QModelIndex &index) const;
    QString fileName(const QModelIndex &index) const;
    FileType fileType(const QModelIndex &index) const;
    QIcon fileIcon(const QModelIndex &index) const;
    bool isDir(const QModelIndex &index) const;
    bool selected(const QModelIndex &index) const;

    explicit GoogleFileSystemModel(QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // GOOGLEFILESYSTEMMODEL_H
