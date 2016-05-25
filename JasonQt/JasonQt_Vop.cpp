#include "JasonQt_Vop.h"

using namespace JasonQt_Vop;

BaiduVop::BaiduVop(const QString &apiKey, const QString &secretKey):
    m_apiKey(apiKey),
    m_secretKey(secretKey)
{
    const auto &&availableDevices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    if(!availableDevices.isEmpty())
    {
        m_currentDevice = availableDevices.first();

        QAudioFormat format;
        format.setSampleRate(8000);
        format.setChannelCount(1);
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setCodec("audio/pcm");

        m_audioInput = new QAudioInput(m_currentDevice, format, this);
    }
}

void BaiduVop::setDevice(const QAudioDeviceInfo &device)
{
    m_currentDevice = device;
}

bool BaiduVop::refreshToken(void)
{
    QNetworkRequest request(QUrl(QString("https://openapi.baidu.com/oauth/2.0/token?")));
    QByteArray append = QString("grant_type=client_credentials&client_id=%1&client_secret=%2&").arg("54GzQbyspseUfRUbvDdVMKQW").arg("9dfXhqPz0F6RrpoNLAzMzkBLz4fpHPu9").toLatin1();
    QByteArray buf;

    request.setRawHeader("Content-Type", "application/json");

    const auto &&flag = m_http.post(request, append, buf, 15000);
    if(!flag) { return false; }

    const auto &&data = QJsonDocument::fromJson(buf).object();
    if(data.isEmpty() || !data.contains("access_token")) { return false; }

    m_token = data["access_token"].toString();
    return true;
}

bool BaiduVop::start(void)
{
    if(m_token.isEmpty())
    {
        qDebug("BaiduVop::start fail, Need refresh token befor start.");
        return false;
    }

    m_buffer = new QBuffer;
    m_buffer->open(QIODevice::ReadWrite);
    m_audioInput->start(m_buffer);

    return true;
}

std::pair<bool, QString> BaiduVop::finish(void)
{
    m_audioInput->stop();

    const auto &sendData = m_buffer->data();
    m_buffer->deleteLater();

    QNetworkRequest request(QUrl("http://vop.baidu.com/server_api"));
    QJsonObject append;

    request.setRawHeader("Content-Type", "application/json");

    append["format"] = "pcm";
    append["rate"] = 8000;
    append["channel"] = 1;
    append["token"] = m_token;
    append["lan"] = "zh";
    append["cuid"] = "JasonQt";
    append["speech"] = QString(sendData.toBase64());
    append["len"] = sendData.size();

    QByteArray buf;
    m_http.post(request, QJsonDocument(append).toJson(), buf, 15000);

    QJsonObject acceptedData(QJsonDocument::fromJson(buf).object());

    if(buf.isEmpty() || acceptedData.isEmpty() || !acceptedData.contains("result")) { return { false, buf }; }

    const auto &&message = acceptedData["result"].toArray()[0].toString();
    return { true, message.mid(0, message.size() - 1) };
}
