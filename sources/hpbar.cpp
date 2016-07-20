#include "hpbar.h"
#include "QQuickView"
#include "QQmlContext"
#include "QQmlEngine"
#include "QQmlComponent"
Hpbar::Hpbar()
{
    sao_hpbar.setFlags(Qt::FramelessWindowHint);
    sao_hpbar.setColor(QColor(Qt::transparent));
    sao_hpbar.setSource(QUrl("qrc:/sao_hpbar.qml"));
}
int Hpbar::show(){
    sao_hpbar.show();
    sao_hpbar.rootContext()->setContextProperty("mainwindow",&sao_hpbar);
}
void Hpbar::setXY(float saohpbarX, float  saohpbarY){
    sao_hpbar.setX(saohpbarX);
    sao_hpbar.setY(saohpbarY);
}
