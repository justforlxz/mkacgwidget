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
class playerData;

class player : public QObject
{
     Q_OBJECT

public:
    player();
    player(const player &);
    player &operator=(const player &);
    QVector<QString>  json();
    QList<QString> list_url;
    QList<QString> list_name;
    ~player();

signals:
    void sig_disp();
    void sig(QVariant str_num);
public slots:
    void slot_hex2dec();

private:
    QSharedDataPointer<playerData> data;
};

#endif // PLAYER_H
