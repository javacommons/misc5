// ItemLayout.qml

import QtQuick 2.15

Rectangle {
    id: _root
    width: 160
    height: 60
    // 枠線
    border.color: "#dddddd"
    border.width: 1

    // 実際に表示する部分へのエイリアス
    property alias number: _layoutNumber.text
    property alias text: _layoutText.text

    // 上位への通知用のシグナル
    signal clicked(string itemText)

    // 表示アイテムを配置
    Row{
        anchors.centerIn: parent
        spacing: 5
        Text{
            id: _layoutNumber
            width: 20
            text: ""
        }
        Text{
            id: _layoutText
            width: 80
            text: ""
        }
    }

    // クリック判定
    MouseArea{
        anchors.fill: parent
        onClicked: {
            // クリックシグナルを上位へ
            _root.clicked(_layoutNumber.text + ":" + _layoutText.text);
        }
    }
}
