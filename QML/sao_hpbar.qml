import QtQuick 2.0
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
Item {

    width: 360
    height: 70
    Rectangle {
        width: 352
        height: 62
        anchors.fill: parent
        color:Qt.rgba(0,0,0,0.0)
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 8
        anchors.topMargin: 0
        Image{
            id:hp_bar
            objectName: "hp_bar_objectName"
            source: "qrc:/Images/hp_bar.png"

        }
        Image{
            id:hp_bar_hp
            x: 72.5
            y: 12
            source:"qrc:/Images/hp_green.png"
            visible: false
        }
        Canvas {
            id: mycanvas
            x: 73
            y: 12
            width: 258
            height: 24

          onPaint: {
                  var ctx = getContext("2d")
             // store current context setup
             ctx.save()
             ctx.strokeStyle = 'rgba(0,0,0,0)'
             // create a triangle as clip region
             ctx.beginPath()
             ctx.moveTo(0,0)
             ctx.lineTo(258,0)
             ctx.lineTo(253,15)
             ctx.lineTo(135,15)
             ctx.lineTo(132,24)
             ctx.lineTo(0,24)
             ctx.closePath()
             // translate coordinate system
             ctx.translate(0,0)
             ctx.clip()  // create clip from triangle path
             // draw image with clip applied
             ctx.drawImage('Images/hp_green.png', 0,0)
             // draw stroke around path
             ctx.stroke()
             // restore previous setup
             ctx.restore()

         }
        Component.onCompleted: {
            loadImage("Images/hp_green.png")
        }

        }
        FontLoader {
               id: saofont
               source: "Fonts/SAOUI.ttf"
           }
        Label{
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
        Label{
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
        Label{
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

        MouseArea {
        id: dragRegion1
        anchors.fill: parent
        property point clickPos: "0,0"
        width: 352
        height: 62
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
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
        Rectangle{
            x: 2.5
            y: 13.5
            width: 22
            height: 22

            color:Qt.rgba(0,0,0,0.0)
            Image{
                id:hpbar_icon
                x: 0
                y: 0
            }
            MouseArea{
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
