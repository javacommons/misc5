import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: _root
    visible: true
    width: 350
    height: 250
    title: qsTr("Scroll")

    // リストの情報を表示
    function clickList(list, object, itemText){
        // クリックアイテムをハイライトする
        list.currentIndex = list.indexAt(object.x, object.y);
        // デバッグ表示
        _debugText.text = "num : " + object.number
                      + "\ntext : " + object.text
                      + "\nitemText : " + itemText;
    }

    // リストの配置
    Row{
        spacing: 3

        ListView{
            id: _listLeft
            width: _root.width / 2
            height: _root.height
            ScrollBar.vertical: ScrollBar {
                active: true
            }
            // ハイライト設定
            highlight: ItemHightlight{
                _listObject: _listLeft
            }
            // モデル
            model: Items1{}
            // デリゲート
            delegate: ItemLayout{
                // インスタンスごとに生成される範囲
                id: _layout1
                // 表示レイアウトへ具体的な値をセットする
                number: _number
                text: arrangeText(_text)
                // 表示するデータをアレンジもOK
                function arrangeText(text){
                    return text + "(in left)";
                }
                // クリックイベント
                onClicked: {
                    // こんな風に更に上位へデータや自分のインスタンスを渡すのもできる
                    clickList(_listLeft, _layout1, itemText);
                }
            }
        }

        ListView{
            id: _listRight
            width: _root.width / 2
            height: _root.height
            ScrollBar.vertical: ScrollBar {
                active: true
            }
            // ハイライト設定
            highlight: ItemHightlight{
                _listObject: _listRight
            }
            // モデル
            model: Items2{}
            // デリゲート
            delegate: ItemLayout{
                // インスタンスごとに生成される範囲
                id: _layout2
                // 表示レイアウトへ具体的な値をセットする
                number: _number
                text: arrangeText(_text)
                // 表示するデータをアレンジもOK
                function arrangeText(text){
                    return text + "(in right)";
                }
                // クリックイベント
                onClicked: {
                    // こんな風に更に上位へデータや自分のインスタンスを渡すのもできる
                    clickList(_listRight, _layout2, itemText);
                }
            }
        }
    }
    // 左のリストへフォーカスセットして現在の情報表示
    Rectangle{
        anchors.horizontalCenter: parent.horizontalCenter
        y: 0
        width: 70
        height: 20
        color: "#dd0000"
        Text{
            anchors.centerIn: parent
            text: "Focus left"
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                _listLeft.forceActiveFocus();
                clickList(_listLeft, _listLeft.currentItem
                          , "current selected");
            }
        }
    }
    // 右のリストへフォーカスセットして現在の情報表示
    Rectangle{
        anchors.horizontalCenter: parent.horizontalCenter
        y: 22
        width: 70
        height: 20
        color: "#dd0000"
        Text{
            anchors.centerIn: parent
            text: "Focus right"
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                _listRight.forceActiveFocus();
                clickList(_listRight, _listRight.currentItem
                          , "current selected");
            }
        }
    }

    // 情報表示
    Rectangle{
        x: _debugText.x
        y: _debugText.y
        width: _debugText.width
        height: _debugText.height
        color: "#555555"
    }
    Text{
        id: _debugText
        anchors.centerIn: parent
        text: ""
        color: "#ffffff"
    }
}
