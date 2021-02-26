import QtQuick 2.0

Rectangle {
    id: knobKey
    signal clicked
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
        //text: qsTr("B-Mode")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.textHeight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        //font.pixelSize: height * fontHeight
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
        onClicked: knobKey.clicked()
    }
}
