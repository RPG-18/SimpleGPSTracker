#include <QtCore/QDebug>
#include "storagemodel.h"

StorageModel::StorageModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_volumes.push_back(QStorageInfo::root());
    auto volumes = QStorageInfo::mountedVolumes();
    QRegExp rx("^/storage.+");
    for(const auto volume: volumes)
    {
        if(rx.exactMatch(volume.displayName()))
        {
            m_volumes.push_back(volume);
        }
    }
}

int StorageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_volumes.size();
}

QHash<int, QByteArray> StorageModel::roleNames() const
{
    static QHash<int, QByteArray> roles = {
        {StorageModel::NAME, "name"}
    };

    return roles;
}

QVariant StorageModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case StorageModel::NAME:
        return m_volumes.at(index.row()).displayName();
    default:
        return QVariant();
    }
}

