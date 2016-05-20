import QtQuick 2.0
import QtQuick.Controls 1.4
Item {

    width: 352
    height: 62
    Rectangle {
       anchors.fill: parent
        color:Qt.rgba(0,0,0,0.0)
        Image{
            width: 352
            height: 62
            fillMode: Image.PreserveAspectFit
            source: "qrc:/Images/hp_bar.png"
        }

        MouseArea {
        id: dragRegion1
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
        acceptedButtons: Qt.LeftButton

}
    }
}
