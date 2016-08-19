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
timer->start(100);
connect(timer,SIGNAL(timeout()),
    this,SLOT(startVoice()));
}

void Voice::inputFinish() {

    const auto &&data = m_baiduVop.finish();

    if(data.first) {
        emit Voice::sig(data.second);
        std::cout<<data.second.toStdString();
    } else {
        emit Voice::sig("识别错误");
        std::cout<<data.first;
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
//该函数每100毫秒调用一次。
void Voice::startVoice() {
//如果音量大于30，开始执行说话的操作。
    if(volume>30) {
//如果switchValue为0，开始执行录音操作
         if(switchValue==0) {
             emit start();
             switchValue=1;
             qDebug()<<switchValue<<"这里是开始录音"<<volume;
             time->start();
         } else {
             time->restart();
         }
    } else {
//如果音量小于30，开始执行提交操作
//此处判断是否是说话中
        if(switchValue==0) {
//            qDebug()<<"抱歉，你来到了外太空";
        } else {
//如果不说话了
            if(time->elapsed()>2000) {
                switchValue=0;
                emit end();
                qDebug()<<switchValue<<"这里是结束录音"<<volume;
                qDebug()<<m_baiduVop.baidudata;
            }
        }
    }
}
