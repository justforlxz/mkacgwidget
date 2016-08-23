import QtQuick 2.0
import QtQml 2.2
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0

Item {
    signal xy(string x,string y)
    width: 367
    height: 146

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
            source: "qrc:/Images/hp_bar_ex.png"
            width: 352
            height: 62
            visible: true
            z: 1
        }
        Item {
            x:68
            y:15
            width: 258
            height: 24
            Image {
                id: image
                source:"qrc:/Images/hp_green.png"
                smooth: true
                visible: false
            }
            Image {
                id: mask
                source:"qrc:/Images/hp_green_mask.png"
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
               source: "qrc:/Fonts/SAOUI.ttf"
           }
        Label {
            id:hpbar_name
            x: 35
            y: 12
            width: 36
            height: 27
            color: "#ffffff"
            text:"Kirito"
            visible: true
            font.bold: true
            font.pointSize: 12
            textFormat: Text.AutoText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: saofont.name
        }
        Label {
            id:hpbar_hp
            x: 222
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
            text:"Lv.1"
            color:"#ffffff"
            font.bold: true
            font.pointSize: 10
            textFormat: Text.AutoText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: saofont.name
        }
        Item{
            id: exp
            Image {
                id: exp_image
                x: 0
                y: 47
                z:1
                width: 212
                height: 42
                source: "qrc:/Images/sp_bar.png"
            }
            Image {
                id: exp_sp
                x: 72
                y: 57
                width: 125
                height: 21
                source: "qrc:/Images/sp_green.png"
                smooth: true
                visible: false
            }

            Image {
                id: exp_mask
                x: 72
                y: 57
                width: 125
                height: 21
                source: "qrc:/Images/sp_mask/sp_mask00100.png"
                smooth: true
                visible: false
            }
            Label{
                id: exp_label
                x: 33
                y: 57
                width: 38
                height: 25
                text: "EXP"
                color:"#ffffff"
                font.bold: true
                font.pointSize: 10
                textFormat: Text.AutoText
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: saofont.name
            }
            OpacityMask {
                anchors.fill: exp_mask
                source: exp_sp
                maskSource: exp_mask
            }
        }

        Item{
            id: sp
            x: 0
            y: 48
            Image {
                id: sp_image
                x: 0
                y: 38
                z:1
                width: 212
                height: 42
                source: "qrc:/Images/sp_bar.png"
            }
            Image {
                id: sp_sp
                x: 72
                y: 48
                width: 125
                height: 21
                source: "qrc:/Images/sp_green.png"
                smooth: true
                visible: false
            }

            Image {
                id: sp_mask
                x: 72
                y: 48
                width: 125
                height: 21
                source: "qrc:/Images/sp_mask/sp_mask00100.png"
                smooth: true
                visible: false
            }
            Label{
                id: sp_label
                x: 33
                y: 48
                width: 38
                height: 25
                text: "SP"
                color:"#ffffff"
                font.bold: true
                font.pointSize: 10
                textFormat: Text.AutoText
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: saofont.name
            }
            OpacityMask {
                anchors.fill: sp_mask
                source: sp_sp
                maskSource: sp_mask
            }
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
            xy(mainwindow.x+delta.x,mainwindow.y+delta.y)
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
     function  setValue(lv,exp,Minute,mask){
         exp_mask.source="qrc:/Images/sp_mask/sp_mask00"+mask+".png";
         hpbar_level.text="Lv."+lv;
         hpbar_hp.text=Minute+"/"+exp;

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
