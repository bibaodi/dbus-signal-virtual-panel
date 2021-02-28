import QtQuick 2.5
import EsiModule 1.0

Rectangle {
    id: knobKey
    signal clicked(int press)
    width: 100
    height: 100
    border.width: 1
    property alias text: keyname.text
    property bool pressed: mouse.pressed
    border.color: "white"
    color: 'gray'

    Text {
        id: keyname
        anchors.fill: parent
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.textHeight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "#1b1c1d"
        font.family: "Open Sans Regular"
    }
    Rectangle {
        Text {
            text: qsTr("left")
            color: "#00FF00"
        }
        x: 5
        y: 5
        width: 40
        height: 40
        color: "#2eaf39" //green
    }
    Rectangle {
        Text {
            text: qsTr("right")
            color: "#00FF00"
        }
        x: 55
        y: 5
        width: 40
        height: 40
        color: "#2eaf39"
    }
    Rectangle {
        Text {text: qsTr("Press");color: "#00FF00"}
        x: 10
        y: 55
        width: 80
        height: 40
        color: "#2eaf39"
    }

    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: function () {
            knobKey.clicked(2);
        }
    }
}
