#ifndef VOICE_H
#define VOICE_H
#include <QObject>
#include <QtCore>
#include "JasonQt/JasonQt_Vop.h"
#include "QDBusInterface"
#include "QDBusMessage"
#include "headers/dbusaudiosource.h"
class Voice: public QObject
{
      Q_OBJECT
public:
    Voice();
    QString backText;
    QTimer *t = new QTimer(this);
    QThread     *m_pTimerThread; //定时器依赖线程
    float volume;
    ~Voice();
signals:
    void sig(QVariant str_num);
    void send_time();
    void start_time();

public slots:
    void inputFinish();
    void startInput();
    void handleMeterVolumeChanged(const QDBusMessage &msg);
    void timer();
private:
        JasonQt_Vop::BaiduVop m_baiduVop;
        DBusAudioSource     *m_defaultSource = nullptr;
        QDBusInterface      *m_dbusMeter    = nullptr;
        QTimer              *m_meterTimer   = nullptr;
};

#endif // VOICE_H
