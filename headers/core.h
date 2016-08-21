#ifndef CORE_H
#define CORE_H

#include <QObject>
#include "headers/JasonQt/JasonQt_Vop.h"
#include "headers/hpbar.h"
#include "headers/player.h"
#include "headers/Voice.h"
#include "headers/settings.h"
#include "QDesktopWidget"
class Core : public QObject
{
     Q_OBJECT
public:
    Core();
    void run(float width,float height);
    //设置类 settings
        Settings* st=new Settings();
    //电量类 Hpbar
        Hpbar* hpbar=new Hpbar();
    //虚拟助理 hajime
        Player* player=new Player();

};

#endif // CORE_H
