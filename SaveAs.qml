import QtQuick 2.6
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import org.simplegpstrack.gpstrack 1.0

Item {
    id: item

    function setFileName(name){
        fileName.text = name;
    }

    signal done(string path)

    StorageModel{
        id: storages
    }
    FileSystemModel{
        id: files
    }

    ColumnLayout{
        id: layout
        anchors.fill: parent
        RowLayout{
            Layout.fillWidth: true
            Button{
                contentItem: Image{
                    anchors.centerIn: parent
                     source: "qrc:/images/back.png"
                }

                onClicked: {
                    files.cdUp();
                }

                text:"Up"
            }

            ComboBox{
                Layout.fillWidth: true

                width: parent.width
                model: storages
                displayText: "Storage: " + currentText
                onActivated:{
                    files.cd(currentText);
                }
            }
        }

        ListView{
            clip:true
            Layout.fillWidth: true
            Layout.fillHeight: true

            model: files

            delegate: Item{
                width: parent.width
                implicitHeight:Math.max(icon.height, label.height)*1.25

                RowLayout {
                    anchors.fill: parent
                    spacing: 6
                    Image{
                        id: icon
                        source: isDir ? "qrc:/images/folder.png" : "qrc:/images/file.png"
                    }
                    Label{
                        id: label
                        Layout.fillWidth: true
                        text: name
                    }
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        if(isDir){
                            files.cd(absoluteFilePath);
                        }
                    }
                }
            }
        }

        RowLayout{
            Layout.fillWidth: true

            TextField{
                id: fileName
                Layout.fillWidth: true
            }

            Button{
                text:"OK"
                onClicked: {
                    if(files.currentPath != "/"){
                        item.done(files.currentPath+"/"+fileName.text);
                    }else{
                        item.done(files.currentPath + fileName.text);
                    }
                }
            }
        }
    }

}
