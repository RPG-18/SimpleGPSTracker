#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QtCore/QDir>
#include <QtCore/QAbstractListModel>

class FileSystemModel: public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString currentPath READ currentPath NOTIFY currentPathChanged)
public:

    enum Roles
    {
        NAME,
        IS_DIR,
        ABSOLUTE_FILE_PATH
    };

    FileSystemModel(QObject* parent = nullptr);

    QString currentPath() const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames() const;

public slots:

    void cd(const QString& path);
    void cdUp();

signals:

    void currentPathChanged();

private:

    void listenDirectory();

private:

    QDir m_dir;
    QFileInfoList m_content;

};

#endif // FILESYSTEMMODEL_H
