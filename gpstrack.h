#ifndef GPSTRACK_H
#define GPSTRACK_H

#include <QtCore/QObject>
#include <QtCore/QDataStream>
#include <QtCore/QTemporaryFile>

#include <QtPositioning/QGeoCoordinate>

class GPSTrack : public QObject
{
    Q_OBJECT
public:

    explicit GPSTrack(QObject *parent = 0);

signals:

public slots:

    void open();
    void append(const QGeoCoordinate& coordinate);

    void saveAsGdx(const QString& file);

private:

    QDataStream m_stream;
    QTemporaryFile m_track;
};

#endif // GPSTRACK_H
