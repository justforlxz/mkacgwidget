#include "headers/hpbar.h"

#include <QDBusInterface>
#include "QDBusReply"
Hpbar::Hpbar():m_powerInter(new DBusPower())
{
    viwer.setFlags(Qt::FramelessWindowHint);
    viwer.setColor(QColor(Qt::transparent));

    viwer.setSource(QUrl("qrc:/sao_hpbar.qml"));

    QObject *viwerObject = viwer.rootObject();

    QObject::connect(m_powerInter,SIGNAL(BatteryPercentageChanged()),\
                 this,SLOT(BatteryPercentageChanged()));
    QObject::connect(m_powerInter,SIGNAL(BatteryStateChanged()),\
                     this,SLOT(BatteryPercentageChanged()));
    QObject::connect(this,SIGNAL(propertyUpdate(QVariant)),\
                 viwerObject,SLOT(propertyUpdatetoQML(QVariant)));
    QObject::connect(this,SIGNAL(propertyState(QVariant)),\
                     viwerObject,SLOT(propertyStatetoQML(QVariant)));
    QObject::connect(viwerObject,SIGNAL(xy(QString,QString)),\
                     this,SLOT(XY(QString,QString)));
}
int Hpbar::show(){
    viwer.show();
    viwer.rootContext()->setContextProperty("mainwindow",&viwer);
    BatteryPercentageChanged();
}
void Hpbar::setXY(float saohpbarX, float  saohpbarY){
    qDebug()<<saohpbarX<<saohpbarY;
    viwer.setX(saohpbarX);
    viwer.setY(saohpbarY);
}
void Hpbar::BatteryPercentageChanged(){
 const int percentage = m_powerInter->batteryPercentage()["Display"];
 BatteryPercentage=percentage;
 const bool plugged = !m_powerInter->onBattery();
 if(plugged==true){
      qDebug()<<"连接电源";
       emit Hpbar::propertyUpdate(BatteryPercentage);
      emit Hpbar::propertyState("true");
 } else {
      qDebug()<<"断开电源";
       emit Hpbar::propertyUpdate(BatteryPercentage);
       emit Hpbar::propertyState("false");
 }
}
void Hpbar::setValue(float lv, float exp) {

}
void Hpbar::XY(QString x, QString y){
    emit Hpbar::getXY(x.toDouble(),y.toDouble());
}
