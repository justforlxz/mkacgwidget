#ifndef SETTINGS_H
#define SETTINGS_H


#include <QObject>
#include <QtCore>

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
    float lv              = 1;
    float exp             = 0;
    int Minute          = 0;

signals:
    void setHpbar_Lv_Exp(float setlv,float setexp);
    void setHpbar_XY(float setx,float sety);
    void setPlayer_XY(float setx,float sety);
public slots:
    void setLv_exp();
    void setSettings();
    void getHpbar_Lv_Exp(float setlv,float setexp);
    void getHpbar_XY(float setx,float sety);
    void getPlayer_XY(float setx,float sety);

};

#endif // SETTINGS_H
