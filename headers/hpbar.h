#ifndef HPBAR_H
#define HPBAR_H
#include <QObject>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlContext>
#include <QtCore>
#include "headers/dbuspower.h"

class Hpbar: public QObject
{
       Q_OBJECT

public:
    explicit Hpbar();
    int show();
    float saohpbarX       = 0;
    float saohpbarY       = 0;
    void setXY(float saohpbarX,float saohpbarY);
    QQuickView viwer;

    QVariant  BatteryPercentage=100;

signals:
    void propertyUpdate(QVariant str_num);
    void propertyState(QVariant str_num);


public slots:
    void BatteryPercentageChanged();

private:
    DBusPower *m_powerInter;
};

#endif // HPBAR_H
