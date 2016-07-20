#ifndef VOICE_H
#define VOICE_H
#include <QObject>
#include <QtCore>
#include "JasonQt/JasonQt_Vop.h"
class Voice: public QObject
{
      Q_OBJECT
public:
    Voice();
    QString backText;
    ~Voice();
signals:
    void sig(QVariant str_num);
    void send_time();
    void start_time();

public slots:
    void inputFinish();
    void startInput();
private:
        JasonQt_Vop::BaiduVop m_baiduVop;
};

#endif // VOICE_H
