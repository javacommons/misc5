import QtQuick 2.15

Rectangle {
    id: _root

    property variant _listObject: null

    width: (_listObject.currentItem === null) ? 0 : _listObject.currentItem.width
    height: (_listObject.currentItem === null) ? 0 : _listObject.currentItem.height
    y: (_listObject.currentItem === null) ? 0 : _listObject.currentItem.y;
    color: "#dddd00"
    Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
}
