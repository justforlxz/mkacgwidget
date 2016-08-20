import QtQuick 2.0
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0

Item {

    width: 360
    height: 121

    Rectangle {
        width: 352
        height: 62
        anchors.fill: parent
        color: "transparent"
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 8
        anchors.topMargin: 0
        Image {
            id: hp_bar
            source: "../Images/hp_bar.png"
            width: 352
            height: 62
            z: 1
        }

        Item {
            x:72.5
            y:12
            width: 258
            height: 24
            Image {
                id: image
                width: 258
                height: 24
                source:"../Images/hp_green.png"
                smooth: true
                visible: false
            }
            Image {
                id: mask
                width: 258
                height: 24
                source:"../Images/hp_green_mask.png"
                smooth: true
                visible: false
            }

            OpacityMask {
                anchors.fill: mask
                source: image
                maskSource: mask
            }
        }
        FontLoader {
               id: saofont
               source: "../Fonts/SAOUI.ttf"
           }
        Label {
            id:hpbar_name
            x: 35
            y: 12
            width: 36
            height: 27
            color: "#ffffff"
            text:"Kirito"
            font.bold: true
            font.pointSize: 12
            textFormat: Text.AutoText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: saofont.name
        }
        Label {
            id:hpbar_hp
            x: 218
            y: 36
            width: 74
            height: 23
            text:"14500/14500"
            color:"#ffffff"
            font.bold: true
            font.pointSize: 10
            textFormat: Text.AutoText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: saofont.name
        }
        Label {
            id:hpbar_level
            x: 301
            y: 39
            width: 36
            height: 16
            text:"Lv.96"
            color:"#ffffff"
            font.bold: true
            font.pointSize: 10
            textFormat: Text.AutoText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: saofont.name
        }
        Image {
            id: sp
            x: -1
            y: 44
            width: 212
            height: 42
            source: "../Images/sp_bar.png"
        }
        Image {
            id: sp_hp
            x: 72
            y: 54
            width: 125
            height: 21
            source: "../Images/sp_green.png"
        }

        MouseArea {
        id: dragRegion1
        anchors.fill: parent
        property point clickPos: "0,0"
        x: 0
        width: 352
        height: 62
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: -8
        anchors.topMargin: 0
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
        acceptedButtons: Qt.LeftButton

        }


    }
    function propertyUpdatetoQML(str_num) {
        console.log(str_num)
           mask.source="qrc:/Images/hp_mask/hp_mask00"+str_num+".png";
        //判断电量，选择不同的图片
          if(str_num>50) {
                image.source="qrc:/Images/hp_green.png"
          } else if(str_num<=50||str_num>=30) {
                image.source="qrc:/Images/hp_yellow.png"
          } else {
                image.source="qrc:/Images/hp_red.png"
          }

    }
     function propertyStatetoQML(str_num) {
        if(str_num == "true") {
            hp_bar.source="qrc:/Images/hp_bar_ex.png"
        } else {
             hp_bar.source="qrc:/Images/hp_bar.png"
        }
     }
        Rectangle {
            x: 2.5
            y: 13.5
            width: 22
            height: 22

            color:Qt.rgba(0,0,0,0.0)
            Image {
                id:hpbar_icon
                x: 0
                y: 0
            }
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                                   hpbar_icon.source="qrc:/Images/icon_hover.png";
                              }

                              onExited: {
                                   hpbar_icon.source="qrc:/Images/icon_normal.png";
                              }
            }
            Component.onCompleted: {
                hpbar_icon.source="qrc:/Images/icon_normal.png";
            }
        }

}
