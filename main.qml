import QtQuick 2.8
import QtQuick.Window 2.2

import hikvision.items 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Launching {
        id: launching_rect
        anchors.fill: parent

        onShowGameItem: {
            launching_rect.visible = false;
            game_item.visible = true;
            game_item.Start();
        }
    }

    GameItem {
        id: game_item
        anchors.fill: parent
        visible: false

        MouseArea {
            id: mosue_area
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
        }
    }
}
