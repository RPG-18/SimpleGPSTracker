import QtQuick 2.6
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

Item {    
    implicitHeight: columnLayout.height

    ColumnLayout{

        id: columnLayout
        anchors.fill: parent

        Label{
            text:"DURATION"
            Layout.fillWidth: true
            font.pointSize: 9
        }

        Text{
            id: duration
            text: trackStat.duration
            width: 300
            height:50
            fontSizeMode: Text.Fit
            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment:Text.AlignHCenter
            verticalAlignment:  Text.AlignVCenter
            minimumPixelSize: 14; font.pixelSize:100
        }
        Label{
            text:"DISTANCE(km)"
            Layout.fillWidth: true
            font.pointSize: 9
        }

        Text{
            id: distance
            text: trackStat.distanceKm
            width: 300
            height:50
            fontSizeMode: Text.Fit
            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment:Text.AlignHCenter
            verticalAlignment:  Text.AlignVCenter
            minimumPixelSize: 14; font.pixelSize:100
        }


        Label{
            text:"SPEED(kmh)"
            Layout.fillWidth: true
            font.pointSize: 9
        }
        Text{
            id: speed
            text: trackStat.speedKmh
            width: 300
            height:50
            fontSizeMode: Text.Fit
            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment:Text.AlignHCenter
            //verticalAlignment:  Text.AlignVCenter
            minimumPixelSize: 14; font.pixelSize:100
        }
    }
}
