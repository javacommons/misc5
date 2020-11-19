import QtQuick 2.15
import QtQuick.Controls 2.15
import Mine 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: "QML02"
    MyObject {
        id: obj
        onFunc1Called: {
            console.log("onFunc1Called!漢字")
            obj.log("onFunc1Called!(2)漢字")
        }
    }
    Row {
        id: row
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
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
        Button {
            id: button3
            text: qsTr("Button3")
        }
    }

    Button {
        id: button4
        y: 100
        text: qsTr("Button4")
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
