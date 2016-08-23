#include "headers/core.h"

Core::Core() {


        QObject::connect(st,SIGNAL(setHpbar_XY(float,float)),\
                         hpbar,SLOT(setXY(float,float)));

        QObject::connect(st,SIGNAL(setPlayer_XY(float,float)),\
                         player,SLOT(setXY(float,float)));

        QObject::connect(st,SIGNAL(setHpbar_Lv_Exp(int,int,int,int)),\
                         hpbar,SLOT(setValue(int,int,int,int)));

//        QObject::connect(hpbar,SIGNAL(getXY(float,float)),\
//                         st,SLOT(getHpbar_XY(float,float)));

//        QObject::connect(player,SIGNAL(getXY(float,float)),\
//                         st,SLOT(getPlayer_XY(float,float)));


}
void Core::run(float width, float height) {
        st->run(width,height);
        hpbar->show();
        player->show();

}
