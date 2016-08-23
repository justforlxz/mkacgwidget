#include "headers/settings.h"

Settings::Settings(){

}

void Settings::run(float width,float height){
    screenWidth=width;
    screenHeight=height;
    //配置文件区域
        QFile file("./main.ini");
           if (file.exists()) {
               QSettings *configIniRead = new QSettings("main.ini", QSettings::IniFormat);
               //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
               saohpbarX = configIniRead->value("/sao_hpbar/x").toFloat();
               saohpbarY = configIniRead->value("/sao_hpbar/y").toFloat();
               hajimeX   = configIniRead->value("/hajime/x").toFloat();
               hajimeY   = configIniRead->value("/hajime/y").toFloat();
               lv        = configIniRead->value("/sao_hpbar/lv").toFloat();
               exp       = configIniRead->value("/sao_hpbar/exp").toFloat();
               Minute    = configIniRead->value("/sao_hpbar/Minute").toFloat();
               emit Settings::setHpbar_Lv_Exp(lv,exp,Minute,(int)Minute/exp*100);
               emit Settings::setHpbar_XY(saohpbarX,saohpbarY);
               emit Settings::setPlayer_XY(hajimeX,hajimeY);
               timer->start(1000*60*5);
               connect(timer,SIGNAL(timeout()),this,SLOT(setLv_exp()));
               //读入入完成后删除指针
               delete configIniRead;
           } else {
                Settings::setSettings();
           }

}

void Settings::setSettings(){
    //Qt中使用QSettings类读写ini文件
      //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
      QSettings *configIniWrite = new QSettings("main.ini", QSettings::IniFormat);
      //向ini文件中写入内容,setValue函数的两个参数是键值对
      //向ini文件写入内容
      configIniWrite->setValue("/sao_hpbar/x", screenWidth/10.0);
      saohpbarX=screenWidth/10.0;
      //向ini文件写入内容
      configIniWrite->setValue("sao_hpbar/y",screenHeight/15.0);
      saohpbarY=screenHeight/15.0;
      //向ini文件写入内容
      configIniWrite->setValue("hajime/x",screenWidth/1.3);
      hajimeX=screenWidth/1.3;
      //向ini文件写入内容
      configIniWrite->setValue("hajime/y",screenHeight/2.2);
      hajimeY=screenHeight/2.2;

      configIniWrite->setValue("/sao_hpbar/lv",lv);
      qDebug()<<"lv:"<<lv;
      configIniWrite->setValue("/sao_hpbar/exp",exp);
      qDebug()<<"exp:"<<exp;
      configIniWrite->setValue("/sao_hpbar/Minute",Minute);

//      emit Settings::setHpbar_Lv_Exp(lv,exp);
//      emit Settings::setHpbar_XY(saohpbarX,saohpbarY);
//      emit Settings::setPlayer_XY(hajimeX,hajimeY);
}

void Settings::getHpbar_Lv_Exp(int setlv,int setexp){
    lv=setlv;
    exp=setexp;
    Settings::setSettings();

}
void Settings::getHpbar_XY(float setx, float sety){
    saohpbarX=setx;
    saohpbarY=sety;
      qDebug()<<"set Hpbar  XY"<<saohpbarX<<saohpbarY;
    Settings::setSettings();
}
void Settings::getPlayer_XY(float setx, float sety){
    hajimeX=setx;
    hajimeY=sety;
    qDebug()<<"set Player XY"<<setx<<sety;
    Settings::setSettings();

}
void Settings::setLv_exp() {
//五分钟调用一次该函数
//exp初始为5
    qDebug()<<"setLv_exp";
    if(Minute++ == exp) {
        lv++;
        exp=Minute*1.5+5;
    }
    qDebug()<<"Minute:"<<Minute<<"exp:"<<exp;
    Settings::setSettings();
    int mask =(double)Minute/exp*100;
    qDebug()<<"mask:"<<mask;
    emit Settings::setHpbar_Lv_Exp(lv,exp,Minute,mask);
}
