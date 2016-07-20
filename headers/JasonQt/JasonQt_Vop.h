#ifndef __JasonQt_Vop_h__
#define __JasonQt_Vop_h__

// Qt lib import
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QBuffer>

#include <QAudioInput>
#include <QAudioDeviceInfo>
// JasonQt lib import
#include "JasonQt_Net.h"

namespace JasonQt_Vop
{

class BaiduVop: public QObject
{
    Q_OBJECT

private:
    QAudioDeviceInfo m_currentDevice;

    QString m_apiKey;
    QString m_secretKey;
    QString m_token;
    QString apiKey="pxxHWz9KmNsleFBsuWHQ77Hd";
    QString secretKey="b5a9a0eb50d410b0dccd3eec5fc30388";
    QAudioInput *m_audioInput = NULL;
    QByteArray m_buf;
    QBuffer *m_buffer = NULL;

    JasonQt_Net::HTTP m_http;

public:
    BaiduVop(const QString &apiKey, const QString &secretKey);
    void setDevice(const QAudioDeviceInfo &device);

public slots:
    bool refreshToken(void);

    bool start(void);

    std::pair<bool, QString> finish(void);
};

}

#endif//__JasonQt_Vop_h__
