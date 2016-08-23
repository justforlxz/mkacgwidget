#ifndef SETTINGS_H
#define SETTINGS_H


#include <QObject>
#include <QtCore>
#include <QTimer>

class Settings : public QObject
{
     Q_OBJECT
public:
    Settings();
    void run(float width,float height);
    float screenWidth     = 0;
    float screenHeight    = 0;
    float saohpbarX       = 0;
    float saohpbarY       = 0;
    float hajimeX         = 0;
    float hajimeY         = 0;
    float hp              = 500;
    int lv              = 1;
    int exp             = 5;
    int Minute            = 0;
    int count             = 0;
      QTimer *timer = new QTimer(this);

signals:
    void setHpbar_Lv_Exp(int setlv,int setexp,int setMinute,int Mask);
    void setHpbar_XY(float setx,float sety);
    void setPlayer_XY(float setx,float sety);

public slots:
    void setLv_exp();
    void setSettings();
    void getHpbar_Lv_Exp(int setlv,int setexp);
    void getHpbar_XY(float setx,float sety);
    void getPlayer_XY(float setx,float sety);

};

#endif // SETTINGS_H
