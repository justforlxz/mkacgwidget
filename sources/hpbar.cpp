#include "headers/hpbar.h"

#include <QDBusInterface>
#include "QDBusReply"
Hpbar::Hpbar():m_powerInter(new DBusPower())
{
    sao_hpbar.setFlags(Qt::FramelessWindowHint);
    sao_hpbar.setColor(QColor(Qt::transparent));
    sao_hpbar.setSource(QUrl("qrc:/sao_hpbar.qml"));

}
int Hpbar::show(){
    sao_hpbar.show();
    sao_hpbar.rootContext()->setContextProperty("mainwindow",&sao_hpbar);
    QObject *object = sao_hpbar.rootObject();

    QObject::connect(m_powerInter,SIGNAL(BatteryPercentageChanged()),\
                 this,SLOT(propertyChanged()));

    QObject::connect(this,SIGNAL(propertyUpdate(QVariant)),
                 object,SLOT(propertyUpdatetoQML(QVariant)));

}
void Hpbar::setXY(float saohpbarX, float  saohpbarY){
    sao_hpbar.setX(saohpbarX);
    sao_hpbar.setY(saohpbarY);
}
void Hpbar::propertyChanged(){
 const int percentage = m_powerInter->batteryPercentage()["Display"];
    qDebug()<<percentage;
    emit Hpbar::propertyUpdate(percentage);
}
