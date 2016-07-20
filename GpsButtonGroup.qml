import QtQuick 2.6
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

Item {
    id: item

    signal start()
    signal stop()
    signal pause()
    signal resume()

    implicitHeight: startButton.height


    Button {
        id: startButton
        text: "START"
        onClicked: {
            item.start();
            item.state = "running";

        }
        anchors.fill: parent
    }

    Button {
        id: stopButton
        visible: false
        text: "STOP"
        anchors.fill: parent
        onClicked: {
            item.pause();
            item.state = "paused"
        }
    }

    RowLayout {
        id: layout
        visible: false
        anchors.fill: parent
        spacing: 10

        Button {
            id: resumeButton
            text: "RESUME"

            onClicked: {
                item.resume();
                item.state = "running"
            }

            Layout.fillWidth: true
        }

        Button {
            id: endButton
            text: "END"

            onClicked: {
                item.stop();
                item.state = "notrun"

            }

            Layout.fillWidth: true
        }
    }

    states:[
        State {
            name: "notrun"
            PropertyChanges{
                target: startButton
                visible: true
            }
            PropertyChanges {
                target: stopButton
                visible: false
            }
            PropertyChanges{
                target: layout
                visible: false
            }
        },
        State {
            name: "running"

            PropertyChanges{
                target: startButton
                visible: false
            }
            PropertyChanges {
                target: stopButton
                visible: true
            }
            PropertyChanges{
                target: layout
                visible: false
            }
        },
        State {
            name: "paused"

            PropertyChanges{
                target: startButton
                visible: false
            }
            PropertyChanges {
                target: stopButton
                visible: false
            }
            PropertyChanges{
                target: layout
                visible: true
            }
        }
    ]

    state: "notrun"
}
