import QtQuick 2.6
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtPositioning 5.5
import QtLocation 5.6
import org.simplegpstrack.gpstrack 1.0

ApplicationWindow {
    id: app
    visible: true
    width: 300
    height: 480
    title: qsTr("SimpleGpsTracker")

    function generateTrackName(){
        var now = new Date();
        return "track_"+now.toLocaleString(Qt.locale("en_US"),
                                           "yyyyMMdd_hhmm")+".gpx";
    }

    header: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent


            Item { Layout.fillWidth: true }
            ToolButton{
                id: menuButton
                contentItem: Image{
                    anchors.centerIn: parent
                     source: "qrc:/images/menu_icon.png"
                }

                text:"share"

                onClicked: menu.open()

                Menu {
                    id: menu
                    y: menuButton.height*3/4

                    MenuItem {
                        text: "Save track"
                        onClicked:{
                            stack.push(saveAsView);
                            var item = stack.currentItem;
                            item.setFileName(generateTrackName());
                            saveConnection.target = item;
                        }

                        Connections{
                            id: saveConnection
                            onDone:{
                                gpsTrack.saveAsGdx(path);
                                stack.pop();
                            }
                        }
                    }
                }
            }
        }
    }

    GPSTrack{
        id:gpsTrack
    }

    StackView {
        id: stack
        initialItem: trackView
        anchors.fill: parent
    }

    Component {
        id: trackView
        Tracker{
        }
    }

    Component {
        id: saveAsView
        SaveAs{
        }
    }


}
