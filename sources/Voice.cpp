#include "headers/Voice.h"
#include "iostream"
#include <QObject>
#include <QDBusInterface>
#include "QDBusReply"
Voice::Voice():m_baiduVop("pxxHWz9KmNsleFBsuWHQ77Hd", "b5a9a0eb50d410b0dccd3eec5fc30388") {
std::cout<<"构造函数运行了";
std::cout<< "Refresh token:" << m_baiduVop.refreshToken();

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
    QDBusConnection::sessionBus().connect("com.deepin.daemon.Audio",
                                          "/com/deepin/daemon/Audio/Metersource2",
                                          "org.freedesktop.DBus.Properties",
                                          "PropertiesChanged", "sa{sv}as",
                                          this, SLOT(handleMeterVolumeChanged(QDBusMessage)));
// m_baiduVop("pxxHWz9KmNsleFBsuWHQ77Hd", "b5a9a0eb50d410b0dccd3eec5fc30388");
//    t->singleShot(200,this,SLOT(timer()));
//    t->start(1000);
// QObject::connect(t,SIGNAL(timeout()),this,SLOT(timer()));
//     m_meterTimer->start(1000);

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
         qDebug()<<volume;
    }
}
void Voice::timer(){
        qDebug()<<volume;
                if(volume>50.0) {
                    //如果大于0.5，表明说话，然后重新计时
                    qDebug()<<"刷新计时" << "meter change to " << volume;
//                    m_baiduVop.start();
                } else {
                    qDebug()<<"开始计时" << "meter change to " << volume;
    //                QObject::connect(t,SIGNAL(timeout()),SLOT(timer()));
    //                t->singleShot(2000,this,SLOT(timer()));
                }

}
