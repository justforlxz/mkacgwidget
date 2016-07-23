#include <QGuiApplication>
#include <QApplication>
#include "QDesktopWidget"
#include <QScreen>
#include <QQmlProperty>
#include <QObject>
#include "headers/JasonQt/JasonQt_Vop.h"
#include <QtCore>
#include <QtNetwork>
#include <iostream>
#include <QSettings>
#include <QFile>
#include "headers/hpbar.h"
#include "headers/player.h"
#include "headers/Voice.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

//声明变量区域
    float screenWidth     = 0;
    float screenHeight    = 0;
    float saohpbarX       = 0;
    float saohpbarY       = 0;
    float hajimeX         = 0;
    float hajimeY         = 0;
//获取屏幕坐标区域
    QDesktopWidget *deskWgt =QApplication::desktop();
     if (deskWgt) {
         QRect screenRect = deskWgt->screenGeometry();
         screenWidth = screenRect.width();
         screenHeight = screenRect.height();
         std::cout << "screen width:" <<screenWidth << ",height:" << screenHeight << std::endl;
     }
//配置文件区域
    QFile file("./main.ini");
       if (file.exists()) {
           QSettings *configIniRead = new QSettings("main.ini", QSettings::IniFormat);
           //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
           saohpbarX = configIniRead->value("/sao_hpbar/x").toFloat();
           saohpbarY = configIniRead->value("/sao_hpbar/y").toFloat();
           hajimeX   = configIniRead->value("/hajime/x").toFloat();
           hajimeY   = configIniRead->value("/hajime/y").toFloat();
           //读入入完成后删除指针
           delete configIniRead;
       } else {
           //Qt中使用QSettings类读写ini文件
             //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
             QSettings *configIniWrite = new QSettings("main.ini", QSettings::IniFormat);
             //向ini文件中写入内容,setValue函数的两个参数是键值对
             //向ini文件写入内容
             configIniWrite->setValue("/sao_hpbar/x", screenWidth/10.0);
             saohpbarX=screenWidth/10.0;
             //向ini文件写入内容
             configIniWrite->setValue("sao_hpbar/y",screenHeight/15.0);
             saohpbarY=screenHeight/15.0;
             //向ini文件写入内容
             configIniWrite->setValue("hajime/x",screenWidth/1.3);
             hajimeX=screenWidth/1.3;
             //向ini文件写入内容
             configIniWrite->setValue("hajime/y",screenHeight/2.2);
             hajimeY=screenHeight/2.2;
             //写入完成后删除指针
             delete configIniWrite;
       };


//电量类 Hpbar
    Hpbar hpbar;
    hpbar.show();
    hpbar.setXY(saohpbarX,saohpbarY);
//虚拟助理 hajime
    Player player;
    player.show();
    player.setXY(hajimeX,hajimeY);

//释放内存
//    delete player;
//    delete hpbar;
    return app.exec();
}
/**
    窗体坐标代码来自 http://blog.csdn.net/iEearth/article/details/43669821
    配置文件代码来自 http://blog.csdn.net/xwdpepsi/article/details/8523080

  */

