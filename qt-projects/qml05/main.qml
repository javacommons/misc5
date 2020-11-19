import QtQuick 2.15
import QtQuick.Controls 2.15
import Mine 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")
    MyObject {
        id: obj
    }
    Row {
        id: row
        spacing: 10
        Button {
            id: button1
            text: qsTr("Button1")
            onClicked:  obj.func1()
        }

        Button {
            id: button2
            text: qsTr("Button2")
        }
    }
}
