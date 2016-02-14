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
#include <QJsonDocument>
#include <QJsonParseError>
#include <QtCore>
#include <QtNetwork>
#include <QList>
#include <iostream>
using namespace std;

QList<QString> list_url;
QList<QString> list_name;
int play_list_num=0;
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    const QString URLSTR = "http://music.163.com/api/playlist/detail?id=23075108";
    QString code;
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

       //redio
        player pl;
        QMap<QString,QString>::iterator  map;


        QObject *play=object->findChild<QObject*>("player");
        if(play)
              play->setProperty("source",player::url);
        QObject::connect(object,SIGNAL(next()),\
                           &pl,SLOT(slot_hex2dec()));
        QObject::connect(&pl,SIGNAL(sig_disp()),\
                           object,SLOT(loaded_play()));


        return app.exec();
}
void seturl(){

}
