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
#include <QVector>
#include "QQuickView"

class Player : public QObject
{
     Q_OBJECT

public:
    Player();
    QList<QString> list_url;
    QList<QString> list_name;
    QQuickView viwer;

    void show();
    ~Player();

signals:
    void sig_disp();
    void sig(QVariant str_num);
    void sig_hitokoto(QVariant str_num);
    void getXY(float x,float y);
public slots:
    void slot_hex2dec();
    void slot_hitokoto();
    void setXY(float hajimeX,float hajimeY);

};

#endif // PLAYER_H
