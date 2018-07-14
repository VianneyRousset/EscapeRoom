import QtQuick 2.4

Item {
    width: 150
    height: 400

    ListView {
        id: listView
        anchors.fill: parent
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row1
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
                spacing: 10
            }
        }
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }

        Text {
            id: text1
            x: 48
            y: 231
            text: qsTr("Camera 1")
            font.pixelSize: 12
        }

        Text {
            id: text2
            x: 48
            y: 260
            text: qsTr("Camera 2")
            font.pixelSize: 12
        }
    }
}
