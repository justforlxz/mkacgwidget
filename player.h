#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QtCore>
#include <QtNetwork>
#include <QList>
#include <iostream>
#include <string>
class playerData;

class player : public QObject
{
     Q_OBJECT

public:
    player();
    player(const player &);
    player &operator=(const player &);
    QMap<QString,QString> json();
    ~player();
    QList<QString> list_url;
    QList<QString> list_name;
    QMap<QString,QString> map;
    static QString url;
signals:
    void sig_disp();
public slots:
    void slot_hex2dec();

private:
    QSharedDataPointer<playerData> data;
};

#endif // PLAYER_H
