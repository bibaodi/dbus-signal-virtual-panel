import QtQuick 2.6
import QtQml 2.3
import QtQuick.Controls 2.0
import EsiModule 1.0

ApplicationWindow {
    id: root
    width: 300
    height: 480
    visible: true

    Item {
        Timer {
            interval: 150
            running: true
            repeat: true
            onTriggered: {
                time.text = Date().toString()
                if (knob_press.color == '#ff0000') {
                    knob_press.color = "#ffff00"
                }
            }
        }

        Text {
            id: time
        }
    }

    BackEnd {
        id: backend
        onUserNameChanged: {
            console.log("userName is:", userName)
            if ("abc" == userName) {
                txt.color = 'red'
            }
        }
        function delay(delayTime) {
            var timer = new Timer()
            timer.interval = delayTime
            timer.repeat = false
            timer.start()
        }
        onKeySymChanged: {
            var original = this.color
            console.log("onkeysym-changed",
                        ks) /*ks is the parameter from emit function*/
            knob_press.color = '#ff0000'
            label.text = keySym
        }
    }

    TextField {
        id: txt
        text: backend.userName
        placeholderText: qsTr("User name")
        anchors.centerIn: parent

        onEditingFinished: backend.userName = text
    }
    Rectangle {
        id: knob_press
        x: 20
        y: 30
        width: 190
        height: 100
        color: "#ffff00"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                /*this make event emit to self and property changed based on self value*/
                console.log("parent.color is:", parent.color)
                if ('#ff0000' != parent.color) {
                    console.log("currnt color is !red")
                    parent.color = 'red'
                    return 'red'
                } else {
                    console.log("current color is !yellow")
                    parent.color = 'yellow'
                    return 'yellow'
                }
            }
            onDoubleClicked: label.moveTo(mouse.x, mouse.y)
            cursorShape: Qt.ForbiddenCursor
        }
        Text {
            id: label
            font.bold: true
            font.pixelSize: 22
            function moveTo(newX, newY) {
                label.x = newX
                label.y = newY
            }
            text: "KnobPress"
        }
    }
}
