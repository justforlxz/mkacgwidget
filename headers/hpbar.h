#ifndef HPBAR_H
#define HPBAR_H
#include <QObject>
#include "QtCore"
#include <QQuickItem>
#include "QQuickView"
#include "QQmlContext"
#include "QDBusInterface"
#include "QDBusMessage"
#include "headers/dbuspower.h"

class Hpbar: public QObject
{
       Q_OBJECT
public:
    Hpbar();
    int show();
    float saohpbarX       = 0;
    float saohpbarY       = 0;
    void setXY(float saohpbarX,float saohpbarY);
    QQuickView sao_hpbar;

signals:
    void propertyUpdate(QVariant str_num);

public slots:
    void propertyChanged();

private:
    DBusPower *m_powerInter;
};

#endif // HPBAR_H
