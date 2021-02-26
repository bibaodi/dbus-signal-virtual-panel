import QtQuick 2.0

Item {
    Item {
        focus: true
        Keys.onPressed: {
            console.log("KeyReader captured:",
                        event.text);
            event.accepted = true;
        }
    }
}
