import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    signal showGameItem();

    Button {
        anchors.centerIn: parent
        text: "Ok"
        onClicked: {
            console.log("show game item")

            emit: showGameItem();
        }
    }


}
