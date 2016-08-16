#include "headers/Voice.h"
#include "iostream"
#include <QObject>
#include <QDBusInterface>
#include "QDBusReply"
Voice::Voice():m_baiduVop("pxxHWz9KmNsleFBsuWHQ77Hd", "b5a9a0eb50d410b0dccd3eec5fc30388") {
std::cout<<"构造函数运行了";
std::cout<< "Refresh token:" << m_baiduVop.refreshToken();
// m_meterTimer = new QTimer(this);
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
// m_baiduVop("pxxHWz9KmNsleFBsuWHQ77Hd", "b5a9a0eb50d410b0dccd3eec5fc30388");
     m_baiduVop.start();
//     QString meterPath = m_defaultSource->GetMeter().value().path();
//     QString meterName = meterPath;
//     meterName = meterName.replace("/", ".").mid(1);

//     if (m_dbusMeter) {
//         m_dbusMeter->deleteLater();
//     }

//     m_dbusMeter = new QDBusInterface("com.deepin.daemon.Audio",
//                                      meterPath,
//                                      meterName,
//                                      QDBusConnection::sessionBus(),
//                                      this);
//     connect(m_meterTimer, &QTimer::timeout, m_dbusMeter, [&] {
//         m_dbusMeter->call("Tick");
//         m_meterTimer->start(5000);
//     });

     QDBusConnection::sessionBus().connect("com.deepin.daemon.Audio",
                                           "/com/deepin/daemon/Audio/Metersource2",
                                           "org.freedesktop.DBus.Properties",
                                           "PropertiesChanged", "sa{sv}as",
                                           this, SLOT(handleMeterVolumeChanged(QDBusMessage)));
//     m_meterTimer->start(5000);
}

Voice::~Voice() {

}
void Voice::handleMeterVolumeChanged(const QDBusMessage &msg){
 QList<QVariant> arguments = msg.arguments();
 QVariant str;
 foreach (str, arguments) {
    qDebug()<<arguments;
 }
}
