#include <QGuiApplication>
#include <QApplication>
#include <QObject>
#include <QtCore>
#include "headers/core.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    float screenWidth     = 0;
    float screenHeight    = 0;
    //获取屏幕坐标区域
        QDesktopWidget *deskWgt =QApplication::desktop();
         if (deskWgt) {
             QRect screenRect = deskWgt->screenGeometry();
             screenWidth = screenRect.width();
             screenHeight = screenRect.height();
             std::cout << "screen width:" <<screenWidth << ",height:" << screenHeight << std::endl;
         }

Core core;
core.run(screenWidth,screenHeight);
//释放内存
//    delete player;
//    delete hpbar;
    return app.exec();
}
/**
    窗体坐标代码来自 http://blog.csdn.net/iEearth/article/details/43669821
    配置文件代码来自 http://blog.csdn.net/xwdpepsi/article/details/8523080

  */

