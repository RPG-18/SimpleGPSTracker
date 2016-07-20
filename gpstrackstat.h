#ifndef GPSTRACKSTAT_H
#define GPSTRACKSTAT_H

#include <QtCore/QObject>
#include <QtCore/QTimer>

#include <QtPositioning/QGeoCoordinate>

class GPSTrackStat : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(double distance READ distance NOTIFY distanceChanged)
    Q_PROPERTY(QString distanceKm READ distanceKm NOTIFY distanceChanged)

    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(QString speedKmh READ speedKmh NOTIFY speedChanged)

public:

    explicit GPSTrackStat(QObject *parent = 0);

    const QString& duration() const;

    double speed() const;
    QString speedKmh() const;

    double distance() const;
    QString distanceKm() const;

signals:

    void durationChanged();
    void distanceChanged();
    void speedChanged();

public slots:

    void append(const QGeoCoordinate& currentPoint);

    void start();
    void stop();
    void pause();
    void resume();

private slots:

    void onTick();


private:

    void duration2string();


private:

    QTimer* m_timer;

    quint64 m_duration;
    QString m_durationStr;

    QGeoCoordinate m_lastPoint;
    double m_distance;
    double m_speed;
    bool m_isStarted;
};

#endif // GPSTRACKSTAT_H
