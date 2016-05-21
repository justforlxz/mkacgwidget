import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtMultimedia 5.6
import "get_json.js" as Get_json

Item{
    width: 300
    height: 300
    signal next()
    Audio{
        objectName: "player"
        id:player_player
        volume: 1.0
        function do_play_stats_changed()
          {
            if( player_player.playbackState === Audio.StoppedState){
                    next()
            }
          }
          onPlaybackStateChanged: {
            do_play_stats_changed();
          }
          onErrorChanged: {
            console.log("audio error :" + _audio.errorString);
    }
    }
    Rectangle {
       anchors.fill: parent
        color:Qt.rgba(0,0,0,0.0)
        Image{
            id:mainImage
            x: 70
            y: 70
            width: 230
            height: 230
            fillMode: Image.PreserveAspectFit
            source: "Images/back1.png"
        }

        MouseArea {
            id: dragRegion
            anchors.fill: parent
            property point clickPos: "0,0"
            anchors.leftMargin: 64
            anchors.topMargin: 70
            onPressed: {
                clickPos  = Qt.point(mouse.x,mouse.y)
            }
            onPositionChanged: {
                //鼠标偏移量
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                //如果mainwindow继承自QWidget,用setPos
                mainwindow.setX(mainwindow.x+delta.x)
                mainwindow.setY(mainwindow.y+delta.y)

            }
            acceptedButtons: Qt.LeftButton | Qt.RightButton // 激活右键（别落下这个）

            onClicked: {
                if (mouse.button == Qt.RightButton) { // 右键菜单
                    //
                    contentMenu.popup()
                }
            }
        }
        Menu { // 右键菜单
            //title: "Edit"
            id: contentMenu

            MenuItem {
                text: "每日一句"
                onTriggered: {get_hitokoto()}
            }
            Menu {
                title: "换肤"

                MenuItem {
                    text: "默认皮肤"
                    onTriggered:{mainImage.source="Images/back1.png"}
                }
                MenuItem{
                    text: "第二皮肤"
                    onTriggered: {mainImage.source="Images/back2.png"}
                }
            }
            MenuItem {
                id:redio_on
                text: "开启电台"
                onTriggered: {next()}
            }
            MenuItem {

                id:redio_off
                text: "关闭电台"
                visible: false
                onTriggered: {play_stop()}
            }

            MenuSeparator { }
            MenuItem {
                text: "退出"
                onTriggered: {}

            }
        }
        Rectangle {
            id: show_window
            x: 8
            y: 8
            width: 132
            height: 82
            color: "#47eeee"
            border.color: "#fb7b7b"

            Text {
                id: show_window_text
                x: 4
                y: 4
                width: 124
                height: 74
                wrapMode: Text.Wrap

                font.pixelSize: 12
            }
        }
        Component.onCompleted: {

                get_hitokoto()
        }
    }

    function get_hitokoto(){
        Get_json.get("http://api.hitokoto.us/rand?charset=utf-8&encode=json",
                     function(result,json){
                            show_window_text.text=json.hitokoto;
                     })

    }
    function loaded_play(str_num){
        redio_off.visible=true
        redio_on.text="下一曲"

        player_player.pause()
        player_player.source=str_num
        player_player.play()
    }
    function play_stop(){
        redio_off.visible=false
        redio_on.text="开启电台"

        player_player.pause()
    }
}
