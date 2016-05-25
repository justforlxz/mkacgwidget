#include "JasonQt_Net.h"

using namespace JasonQt_Net;

QNetworkAddressEntry JasonQt_Net::getNetworkAddressEntry(void)
{
    auto allInterfaces = QNetworkInterface::allInterfaces();

    // Scan en0
    for(const auto &interface: allInterfaces)
    {
        if(interface.name().indexOf("en0") != -1)
        {
            for(const auto &entry: interface.addressEntries())
            {
                if(entry.ip().toIPv4Address())
                {
                    return entry;
                }
            }
        }
    }

    // Scan other
    for(const auto &interface: allInterfaces)
    {
        for(const auto &entry: interface.addressEntries())
        {
            if(entry.ip().toIPv4Address())
            {
                if(entry.ip().toString().indexOf("10.0.") == 0)
                {
                    return entry;
                }
                else if(entry.ip().toString().indexOf("192.168.") == 0)
                {
                    return entry;
                }
            }
        }
    }

    return QNetworkAddressEntry();
}

QString JasonQt_Net::getDeviceName(void)
{
#ifdef Q_OS_MAC
    return QHostInfo::localHostName().replace(".local", "");
#endif
    return QHostInfo::localHostName();
}

// HTTP
HTTP::HTTP(void)
{
    connect(&m_manage, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    m_timer.setSingleShot(true);
}

void HTTP::get(const QUrl &url, const int &maxTime)
{
    if(m_reply)
    {
        this->stop();
    }

    m_reply = m_manage.get(QNetworkRequest(url));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));

    if(m_timer.isActive())
    {
        m_timer.stop();
    }
    m_timer.start(maxTime);
}

void HTTP::post(const QNetworkRequest &networkRequest, const QByteArray &append, const int &maxTime)
{
    if(m_reply)
    {
        this->stop();
    }

    m_reply = m_manage.post(networkRequest, append);
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));

    if(m_timer.isActive())
    {
        m_timer.stop();
    }
    m_timer.start(maxTime);
}

void HTTP::stop(void)
{
    if(m_reply)
    {
        disconnect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
        m_reply = NULL;
    }

    if(m_timer.isActive())
    {
        m_timer.stop();
    }
}

bool HTTP::get(const QUrl &url, QByteArray &target, const int &maxTime)
{
    QEventLoop eventLoop;

    connect(this, &HTTP::finished, [&](const QByteArray &data)
    {
        target = data;

        eventLoop.exit(1);
    });
    connect(this, &HTTP::error, [&]()
    {
        eventLoop.exit(0);
    });

    this->get(url, maxTime);

    return eventLoop.exec();
}

bool HTTP::post(const QNetworkRequest &networkRequest, const QByteArray &append, QByteArray &target, const int &maxTime)
{
    QEventLoop eventLoop;

    auto c1 = connect(this, &HTTP::finished, [&](const QByteArray &data)
    {
        target = data;

        eventLoop.exit(1);
    });
    auto c2 = connect(this, &HTTP::error, [&]()
    {
        eventLoop.exit(0);
    });

    this->post(networkRequest, append, maxTime);

    const auto &&flag = eventLoop.exec();

    disconnect(c1);
    disconnect(c2);

    return flag;
}

void HTTP::onFinished(QNetworkReply *reply)
{
    if(m_reply == reply)
    {
        if(m_reply->error() != QNetworkReply::NoError)
        {
            emit error(m_reply->error());
        }
        else
        {
            emit finished(m_reply->readAll());
        }

        this->stop();
    }
}

void HTTP::onTimeout(void)
{
    if(m_reply)
    {
        this->stop();
        emit error(QNetworkReply::TimeoutError);
    }
}

void HTTP::onError(const QNetworkReply::NetworkError &error_)
{
    if(m_reply)
    {
        this->stop();
        emit error(error_);
    }
}
