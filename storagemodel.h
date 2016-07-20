#ifndef DISKMODEL_H
#define DISKMODEL_H

#include <QtCore/QStorageInfo>
#include <QtCore/QAbstractListModel>

class StorageModel: public QAbstractListModel
{
    Q_OBJECT

    using Volumes =  QList<QStorageInfo>;


public:

    enum Roles
    {
        NAME = Qt::UserRole + 1
    };

    StorageModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;

private:

    Volumes m_volumes;

};

#endif // DISKMODEL_H
