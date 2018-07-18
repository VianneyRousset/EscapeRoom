import QtQuick 2.4

Item {
    width: 300
    height: 200

    Image {
        id: image
        sourceSize.height: 2000
        sourceSize.width: 300
        anchors.fill: parent
        source: "tree.svg"
    }
}
