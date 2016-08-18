#include "headers/Voice.h"
#include "iostream"
#include <QObject>
#include <QDBusInterface>
#include "QDBusReply"

 #include <unistd.h>
Voice::Voice():m_baiduVop("pxxHWz9KmNsleFBsuWHQ77Hd", "b5a9a0eb50d410b0dccd3eec5fc30388") {
std::cout<<"构造函数运行了";
std::cout<< "Refresh token:" << m_baiduVop.refreshToken();
    QDBusConnection::sessionBus().connect("com.deepin.daemon.Audio",
                                          "/com/deepin/daemon/Audio/Metersource2",
                                          "org.freedesktop.DBus.Properties",
                                          "PropertiesChanged", "sa{sv}as",
                                          this, SLOT(handleMeterVolumeChanged(QDBusMessage)));
switchValue = 0;//0为为开启录音，1为开启录音。
}

void Voice::inputFinish() {

    const auto &&data = m_baiduVop.finish();

    if(data.first) {
        emit Voice::sig(data.second);
        std::cout<<data.second.toStdString();
    } else {
        emit Voice::sig("识别错误");
    }
    std::cout<< "Refresh token:" << m_baiduVop.refreshToken();
}

void Voice::startInput() {
 m_baiduVop.start();
}

Voice::~Voice() {

}
void Voice::handleMeterVolumeChanged(const QDBusMessage &msg){
    QList<QVariant> arguments = msg.arguments();
    QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
    if (changedProps.contains("Volume")) {
//        qDebug() << "meter change to " << changedProps.value("Volume").toDouble()*100;
//        emit inputMeterVolumeChanged(changedProps.value("Volume").toDouble() * 100);
        volume=changedProps.value("Volume").toDouble()*100;
//        qDebug()<<volume;
/*
            if(changedProps.value("Volume").toDouble()*100>40){
//如果没开启录音，判断一下音频,然后发射信号
                 if(switchValue==0) {
                     emit start();
                     switchValue=1;
                     qDebug()<<switchValue<<"这里是开始录音";
                 }
            } else {
//如果音量小于设定值，发射停止信号
                switchValue=0;
                emit end();
                qDebug()<<switchValue<<"这里是结束录音";
            }
            */
    }
}
void Voice::test(){
//  qDebug()<<volume;
//    QDBusConnection::sessionBus().connect("com.deepin.daemon.Audio",
//                                          "/com/deepin/daemon/Audio/Metersource2",
//                                          "org.freedesktop.DBus.Properties",
//                                          "PropertiesChanged", "sa{sv}as",
//                                          this, SLOT(handleMeterVolumeChanged(QDBusMessage)));
    timer->start(500);
    connect(timer,SIGNAL(timeout()),
        this,SLOT(test1()));

}
void Voice::test1(){
    if(volume>30){
//如果没开启录音，判断一下音频,然后发射信号
         if(switchValue==0) {
             emit start();
             switchValue=1;
             qDebug()<<switchValue<<"这里是开始录音"<<volume;
             time->start();
         }
    } else {
//如果音量小于设定值，发射停止信号
        if(switchValue==0){
            qDebug()<<"抱歉，你来到了外太空";
        } else {
            if(time->elapsed()<1500){
                 qDebug()<<"小于三秒，调用个屁开始";
    //             time->restart();
            } else if(time->elapsed()>3000) {
    //            qDebug()<<"你丫的不说话";
    //            m_baiduVop.stop();
    //            time->restart();
                switchValue=0;
                emit end();
                qDebug()<<switchValue<<"这里是结束录音"<<volume;
            } else {
                    qDebug()<<"我也不知道怎么了，反正就进来了。";
            }
        }
    }
}
