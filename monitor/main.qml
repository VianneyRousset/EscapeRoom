import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Extras 1.4

Window {
    visible: true
    width: 800
    height: 480
    title: qsTr("Monitor")

    TimerForm {
        id: timerForm
        x: 0
        y: 280
    }

    Cameras {
        id: cameras
        x: 620
        y: 40
    }

    Board {
        id: board
        x: 206
        y: 280
    }

    TreeForm {
        id: treeForm
        x: 25
        y: 25
        width: 559
        height: 249
    }
}
