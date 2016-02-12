#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include<QColor>
#include<QQmlContext>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QObject>
#include <QDebug>
#include <QQuickItem>
#include <player.h>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
       QQuickView viwer;
       //无边框，背景透明
       viwer.setFlags(Qt::FramelessWindowHint);
       viwer.setColor(QColor(Qt::transparent));
       //加载qml，qml添加到资源文件中可避免qml暴露
       viwer.setSource(QUrl("qrc:/main.qml"));
       viwer.show();
       //将viewer设置为main.qml属性
       viwer.rootContext()->setContextProperty("mainwindow",&viwer);
       QObject *object = viwer.rootObject();
       //QObject *rect = object->findChild<QObject*>("rect");
        QObject *play=object->findChild<QObject*>("player");
        if(play)
            play->setProperty("source","http://m2.music.126.net/M6SbDY4_KTTXy-XKVse8Jg==/7735064302565150.mp3");
        player pl;
        QObject::connect(object,SIGNAL(next()),\
                           &pl,SLOT(slot_hex2dec()));
        QObject::connect(&pl,SIGNAL(sig_disp()),\
                           object,SLOT(loaded_play()));



       return app.exec();
}
