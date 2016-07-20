#include <QtCore/QDebug>

#include <algorithm>

#include "filesystemmodel.h"

FileSystemModel::FileSystemModel(QObject* parent)
    : QAbstractListModel(parent)
    , m_dir(QDir("/"))
{

    listenDirectory();
}

int FileSystemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_content.size();
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    const auto row = index.row();
    if(m_content.size() < row)
    {
        return QVariant();
    }

    const auto& item = m_content[row];
    switch (role) {
    case NAME:
        return item.fileName();
    case IS_DIR:
        return item.isDir();
    case ABSOLUTE_FILE_PATH:
        return item.absoluteFilePath();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> FileSystemModel::roleNames() const
{
    static QHash<int, QByteArray> roles = {
        {NAME,               "name"},
        {IS_DIR,             "isDir"},
        {ABSOLUTE_FILE_PATH, "absoluteFilePath"}
    };

    return roles;
}

void FileSystemModel::listenDirectory()
{
    m_content = m_dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files,
                                    QDir::DirsFirst | QDir::Name);
}

 void FileSystemModel::cd(const QString& path)
 {
     beginResetModel();
     m_dir = QDir(path);
     listenDirectory();
     endResetModel();
     emit currentPathChanged();
 }

 void FileSystemModel::cdUp()
 {
     if(m_dir.cdUp())
     {
         beginResetModel();
         listenDirectory();
         endResetModel();
         emit currentPathChanged();
     }
 }

 QString FileSystemModel::currentPath() const
 {
     return m_dir.absolutePath();
 }

