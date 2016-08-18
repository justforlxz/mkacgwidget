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
    QTimer *timer = new QTimer(this);
    QTime *time = new QTime();
    float volume;
    int switchValue;
    ~Voice();
signals:
    void sig(QVariant str_num);
    void send_time();
    void start_time();
    void start();
    void end();

public slots:
    void inputFinish();
    void startInput();
    void handleMeterVolumeChanged(const QDBusMessage &msg);
    void startVoice();

private:
        JasonQt_Vop::BaiduVop m_baiduVop;
        DBusAudioSource     *m_defaultSource = nullptr;
        QDBusInterface      *m_dbusMeter    = nullptr;
        QTimer              *m_meterTimer   = nullptr;
};

#endif // VOICE_H
