import QtQuick 2.6
import QtQml 2.3
import QtQuick.Controls 2.0
import EsiModule 1.0
import QtQuick.Window 2.12
import EvFilter 1.0

//ApplicationWindow {
 Window {
    id: root
    objectName: "root-window"
    width: 480
    height: 300
    visible: true

    Rectangle {
        objectName: "rect01"
        width: 200; height: 200
        Keys.onPressed: {
            console.log("Keys.onPressed-Captured:", event.text);
            switch (event.text) {
                case "a":
                    knob_key_01s.itemAt(0).clicked(1);
                    break;
                case "s":
                    knob_key_01s.itemAt(1).clicked(1);
                    break;
                case "d":
                    knob_key_01s.itemAt(2).clicked(1);
                    break;
                case "f":
                    knob_key_01s.itemAt(3).clicked(1);
                    break;
                default:
                    console.log("not bind keys")
            }
        }
        Keys.onReleased: {
            switch (event.text) {
                case "a":
                    knob_key_01s.itemAt(0).clicked(0);
                    mouse.cursorShape = Qt.ArrowCursor;
                    console.log("enabled? =", mouse.enabled, mouse.cursorShape);
                    break;
                case "s":
                    knob_key_01s.itemAt(1).clicked(0);
                    mouse.cursorShape =Qt.ArrowCursor;
                    console.log("enabled? =", mouse.enabled, mouse.cursorShape);
                    break;
                case "d":
                    knob_key_01s.itemAt(2).clicked(0);
                    break;
                case "f":
                    knob_key_01s.itemAt(3).clicked(0);
                    break;
                default:
                    console.log("Keys.onReleased: not bind keys")
            }

        }
        Loader {
            id: loader
            focus: true
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                loader.source = "KeyReader.qml"
            }
        }
    }

    //Column {
    Repeater {
        id: knob_key_01s
        model: ["R1", "R2", "R3", "R4"]
        KnobKey {
            objectName: "key_"+modelData
            x: (index % 4) * width
            y: Math.floor(index / 4 + 1) * height
            text: modelData
            color: pressed ? "#d6d6d6" : "#eeeeee"
            onClicked: function (press) {
                console.log(eventName, "objectName:", this.objectName, "press=", press);
                if (1 === press) {
                color = "#d6d6d6" ;
                } else {
                color = "#eeeeee";}
            }

            property string eventName: {
                return objectName
            }
        }
    }
    MouseArea {
        id: globalMouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: EvFilter.cursor() ? Qt.ArrowCursor: Qt.BlankCursor

    }
    MouseArea {
            id: redMouseArea
            width: 150
            height: 150
            cursorShape: containsMouse ? Qt.OpenHandCursor : Qt.ArrowCursor
            enabled: false

            readonly property bool containsMouse: {
                var relativePos = mapFromItem(globalMouseArea, globalMouseArea.mouseX, globalMouseArea.mouseY);
                return contains(Qt.point(relativePos.x, relativePos.y));
            }

            Rectangle {
                anchors.fill: parent
                color: "red"
            }
        }
        Rectangle {
            id: greenMouseArea
            x: 50
            y: 50
            width: 150
            height: 150
            color: containsMouse ? "brown" : "green"

            readonly property bool containsMouse: {
                var relativePos = mapFromItem(globalMouseArea, globalMouseArea.mouseX, globalMouseArea.mouseY);
                return contains(Qt.point(relativePos.x, relativePos.y));
            }

            Connections {
                target: globalMouseArea
                onPressed: {
                    if (greenMouseArea.containsMouse) {
                        greenMouseArea.pressed();
                        EvFilter.set_cursor(1);
                    } else {
                        EvFilter.set_cursor(-1);
                    }
                }
            }

            signal pressed
            onPressed: console.log("Ahoj!")
        }
    Component.onCompleted: {  EvFilter.listenTo(root);}
    //}
}
