#include <QtCore/QFile>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QDataStream>
#include <QtCore/QXmlStreamWriter>

#include "gpstrack.h"

namespace
{
struct TrackPoint
{
    QDateTime dtime;
    QGeoCoordinate coordinate;
};


}
QDataStream &operator<<(QDataStream & stream, const TrackPoint & point)
{
    stream<<point.dtime<<point.coordinate;
    return stream;
}

QDataStream &operator>>(QDataStream & stream, TrackPoint & point)
{
    stream>>point.dtime>>point.coordinate;
    return stream;
}

GPSTrack::GPSTrack(QObject *parent) : QObject(parent)
{

    m_stream.setVersion(QDataStream::Qt_5_6);
    m_stream.setFloatingPointPrecision(QDataStream::DoublePrecision);
}

void GPSTrack::open()
{
    if(m_track.isOpen())
    {
        m_track.close();
    }

    if(!m_track.open())
    {
        qWarning()<<"Error open temporary file!";
    }

    m_track.setAutoRemove(true);
    m_stream.setDevice(&m_track);
}

void GPSTrack::append(const QGeoCoordinate& coordinate)
{
    if(coordinate.isValid()
            && m_track.isOpen())
    {
        const TrackPoint tp{QDateTime::currentDateTimeUtc(),
                     coordinate};
        m_stream<<tp;
    }
}

void GPSTrack::saveAsGdx(const QString& file)
{
    if(m_track.isOpen())
    {
        if(!m_track.seek(0))
        {
            qCritical()<<"Error move to the beginning of the track";
            return;
        }

        QDataStream ist(&m_track);
        ist.setVersion(QDataStream::Qt_5_6);
        ist.setFloatingPointPrecision(QDataStream::DoublePrecision);
        if(ist.atEnd())
        {
            qDebug()<<"Track is empty";
            return;
        }

        QFile ost(file);
        if(!ost.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        {
            qCritical()<<"Error open file"<<file;
        }

        {
            QXmlStreamWriter stream(&ost);
            stream.writeStartDocument();

            stream.writeStartElement("gpx");
            stream.writeStartElement("trk");
            stream.writeStartElement("trkseg");

            while(!ist.atEnd())
            {
                TrackPoint tp;
                ist>>tp;

                stream.writeStartElement("trkpt");
                stream.writeAttribute("lat",
                                      QString::number(tp.coordinate.latitude()));
                stream.writeAttribute("lon",
                                      QString::number(tp.coordinate.longitude()));
                stream.writeTextElement("time", tp.dtime.toString(Qt::ISODate));
                stream.writeEndElement(); //trkpt

            }

            stream.writeEndElement(); //trkseg
            stream.writeEndElement(); //trk
            stream.writeEndElement(); // gpx
            stream.writeEndDocument();
        }
        ost.flush();
        ost.close();
    }
}
