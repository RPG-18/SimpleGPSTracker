#include <QtCore/QTimerEvent>
#include <QtCore/QTextStream>


#include "gpstrackstat.h"

GPSTrackStat::GPSTrackStat(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
    , m_duration(0)
    , m_durationStr("00:00:00")
    , m_distance(0)
    , m_speed(0)
    , m_isStarted(false)
{

    connect(m_timer, &QTimer::timeout,
            this, &GPSTrackStat::onTick);

    m_timer->setInterval(1000);
    m_timer->start();

}

const QString& GPSTrackStat::duration() const
{
    return m_durationStr;
}

double GPSTrackStat::speed() const
{
    return m_speed;
}

QString GPSTrackStat::speedKmh() const
{
    const auto speed = m_speed * 3.6;

    return QString::number(speed, 'g', 2);
}

double GPSTrackStat::distance() const
{
    return m_distance;
}

QString GPSTrackStat::distanceKm() const
{
    const auto distance = m_distance/1000;
    return QString::number(distance, 'g', 3);
}

void GPSTrackStat::start()
{
    m_duration = 0;
    m_distance = 0;
    m_speed = 0;
    m_isStarted = true;
}

void GPSTrackStat::stop()
{
     m_isStarted = false;
}

void GPSTrackStat::pause()
{
    stop();
}

void GPSTrackStat::resume()
{
    m_isStarted = true;
}

void GPSTrackStat::append(const QGeoCoordinate& currentPoint)
{
    if(!m_isStarted)
    {
        return;
    }

    if(m_lastPoint.isValid())
    {
        m_distance = m_distance + currentPoint.distanceTo(m_lastPoint);


        emit distanceChanged();
    }

    m_lastPoint = currentPoint;
}

void GPSTrackStat::onTick()
{
    if(m_isStarted)
    {
        ++m_duration;
        duration2string();
        emit durationChanged();

        if(m_duration != 0)
        {
            m_speed = m_distance / m_duration;
            emit speedChanged();
        }
    }
}


void GPSTrackStat::duration2string()
{
    QString str;
    QTextStream stream(&str);

    const int hours   = m_duration / 3600;
    const int minutes = (m_duration / 60) % 60;
    const int seconds = m_duration % 60;
    stream.setPadChar('0');
    stream<<qSetFieldWidth(2)<<hours<<qSetFieldWidth(1)<<":"
         <<qSetFieldWidth(2)<<minutes<<qSetFieldWidth(1)<<":"
        <<qSetFieldWidth(2)<<seconds;

    m_durationStr.swap(str);
}
