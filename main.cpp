#include <QGuiApplication>
#include <QtQml>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>

#include "gpstrack.h"
#include "gpstrackstat.h"
#include "storagemodel.h"
#include "filesystemmodel.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<GPSTrack>("org.simplegpstrack.gpstrack", 1, 0, "GPSTrack");
    qmlRegisterType<GPSTrackStat>("org.simplegpstrack.gpstrack", 1, 0, "GPSTrackStat");
    qmlRegisterType<StorageModel>("org.simplegpstrack.gpstrack", 1, 0, "StorageModel");
    qmlRegisterType<FileSystemModel>("org.simplegpstrack.gpstrack", 1, 0, "FileSystemModel");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
