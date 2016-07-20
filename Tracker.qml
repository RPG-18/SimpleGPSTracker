import QtQuick 2.6
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtPositioning 5.5
import QtLocation 5.6
import org.simplegpstrack.gpstrack 1.0

Item {
    property bool isRuning: false

    Location {
        id: previous
    }

    PositionSource {
        id: gpsSrc
        updateInterval: 5000
        preferredPositioningMethods: PositionSource.SatellitePositioningMethods


        onPositionChanged: {
            if(!isRuning){
                return;
            }

            var current =  gpsSrc.position.coordinate;

            if(previous.coordinate.isValid
                    && current.isValid
                    && current.distanceTo(previous.coordinate)>10)
            {
                gpsTrack.append(current);
                trackStat.append(current);
                mapView.appendCoordinate(current);

                previous.coordinate = current;
            }
            else if (!previous.coordinate.isValid && current.isValid){

                gpsTrack.append(current);
                trackStat.append(current);
                mapView.appendCoordinate(current);
                previous.coordinate = current;
            }
        }
    }

    GPSTrackStat{
        id:trackStat
    }

    Plugin {
         id: mapPlugin
         name: "osm"
         PluginParameter {
             name: "osm.mapping.host";
             value: "http://a.tile.openstreetmap.org/"
         }
    }

    ColumnLayout{
        id: layout
        anchors.fill: parent
        spacing: 20

        MapView {
            id: mapView
            z: 1

            Layout.fillWidth: true
            Layout.preferredHeight: app.height * 0.4
        }

        TrackCharacteristics{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        GpsButtonGroup{
            id: buttonGroup
            visible: true

            width: app.width;

            Layout.fillWidth: true

            onStart:{
                isRuning = true;
                gpsTrack.open();
                gpsSrc.start();
                trackStat.start();
                mapView.start();
            }

            onStop:{
                isRuning = false;
                gpsSrc.stop();
                trackStat.stop();
            }

            onPause:{
                gpsSrc.stop();
                trackStat.pause();
            }

            onResume:{
                gpsSrc.start();
                trackStat.resume();
            }
        }
    }
}
