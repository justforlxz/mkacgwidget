#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QColor>
#include <QQmlContext>
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
       QQuickView viwer;
       //无边框，背景透明
       viwer.setFlags(Qt::FramelessWindowHint);
       viwer.setColor(QColor(Qt::transparent));

       //加载qml，qml添加到资源文件中可避免qml暴露
       viwer.setSource(QUrl("qrc:/main.qml"));
       viwer.show();


       QQuickView sao_hpbar;
       sao_hpbar.setFlags(Qt::FramelessWindowHint);
       sao_hpbar.setColor(QColor(Qt::transparent));
        sao_hpbar.setSource(QUrl("qrc:/sao_hpbar.qml"));
        sao_hpbar.show();


       sao_hpbar.rootContext()->setContextProperty("mainwindow",&sao_hpbar);

       //将viewer设置为main.qml属性
       viwer.rootContext()->setContextProperty("mainwindow",&viwer);


       QObject *object = viwer.rootObject();
        player pl;
        QObject::connect(object,SIGNAL(next()),\
                           &pl,SLOT(slot_hex2dec()));
        QObject::connect(&pl,SIGNAL(sig(QVariant)),\
                           object,SLOT(loaded_play(QVariant)));

//        QObject *play=object->findChild<QObject*>("player");
//        if(play)
//              play->setProperty("source",url);

        return app.exec();
}
