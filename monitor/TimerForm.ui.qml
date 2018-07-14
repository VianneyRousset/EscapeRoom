import QtQuick 2.4
import Qt.labs.folderlistmodel 2.2
import QtGraphicalEffects 1.0
import QtGraphicalEffects.private 1.0
import QtQuick.Controls 1.5
import Qt.labs.settings 1.0
import QtQuick.Controls.Styles.Desktop 1.0
import QtQuick.Extras 1.4
import QtQuick.Dialogs.qml 1.0
import QtQuick.Window 2.3
import QtQuick.XmlListModel 2.0
import QtTest 1.2
import QtWayland.Compositor 1.0
import QtWebEngine 1.5
import QtWebEngine.Controls1Delegates 1.0
import QtQuick.Layouts 1.3

Item {
    width: 200
    height: 200

    Dial {
        id: dial
        anchors.fill: parent

        Text {
            id: text1
            text: qsTr("45:36")
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 30
        }
    }
}
