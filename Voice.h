#ifndef VOICE_H
#define VOICE_H
#include "time.h"
#include "JasonQt/JasonQt_Vop.h"
class Voice: public QObject
{
public:
    Voice();
signals:
    void sig_disp();
    void sig(QVariant str_num);
    void send_time();
public slots:
    void inputFinish();
    void startInput();
private:
        JasonQt_Vop::BaiduVop m_baiduVop;
};

#endif // VOICE_H
