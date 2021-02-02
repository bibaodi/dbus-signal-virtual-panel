import QtQuick 2.0

Rectangle {
    width: 100
    height: 100
    color: 'gray'
    Rectangle {
        id: knob_left0
        x: 5
        y: 5
        width: 40
        height: 40
        color: "#2eaf39" //green
    }
    Rectangle {
        id: knob_right0
        x: 55
        y: 5
        width: 40
        height: 40
        color: "#2eaf39"
    }
    Rectangle {
        id: knob_press0
        x: 10
        y: 55
        width: 80
        height: 40
        color: "#2eaf39"
    }
}
