import QtQuick 2.6
import QtQml 2.3
import QtQuick.Controls 2.0
import EsiModule 1.0


ApplicationWindow {
    id: root
    width: 480
    height: 300
    visible: true

    Rectangle {
        width: 200; height: 200
        Keys.onPressed: {
            console.log("Captured:", event.text);
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
                    break;
                case "s":
                    knob_key_01s.itemAt(1).clicked(0);
                    break;
                case "d":
                    knob_key_01s.itemAt(2).clicked(0);
                    break;
                case "f":
                    knob_key_01s.itemAt(3).clicked(0);
                    break;
                default:
                    console.log("not bind keys")
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
                color = "#d6d6d6" ;} else {
                color = "#eeeeee";}
            }

            property string eventName: {
                return objectName
            }
        }
    }
    //}
}
