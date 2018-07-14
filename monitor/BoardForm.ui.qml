import QtQuick 2.4
import QtQuick.Extras 1.4

Item {
    width: 400
    height: 200

    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent

        Text {
            id: text1
            x: 57
            y: 12
            text: qsTr("Coffre")
            font.bold: true
            font.family: "Arial"
            font.pixelSize: 20
        }

        StatusIndicator {
            id: statusIndicator
            x: 19
            y: 9
            color: "#17d200"
            active: true
        }

        ToggleButton {
            id: toggleButton
            x: 244
            y: 19
            text: qsTr("Fermer")
            checked: true
        }

        Rectangle {
            id: rectangle1
            x: 20
            y: 87
            width: 189
            height: 95
            color: "#ffffff"
        }

        Text {
            id: text4
            x: 262
            y: 157
            text: qsTr("Plus d'options")
            font.pixelSize: 12
        }

        Text {
            id: text2
            x: 22
            y: 50
            text: qsTr("Status: Ouvert")
            font.pixelSize: 16
        }

        Text {
            id: text3
            x: 27
            y: 87
            text: qsTr("00:00 - Fermé")
            font.pixelSize: 12
        }

        Text {
            id: text5
            x: 25
            y: 103
            text: qsTr("21:22 - Ouvert")
            font.pixelSize: 12
        }

        Text {
            id: text6
            x: 27
            y: 118
            text: qsTr("21:25 - Fermé")
            font.pixelSize: 12
        }

        Text {
            id: text7
            x: 25
            y: 134
            text: qsTr("22:10 - Forcé ouvert")
            font.pixelSize: 12
        }
    }
}
