#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>


class playerData;

class player : public QObject
{
     Q_OBJECT
public:
    player();
    player(const player &);
    player &operator=(const player &);
    ~player();
signals:
    void sig_disp();
public slots:
    void slot_hex2dec();

private:
    QSharedDataPointer<playerData> data;
};

#endif // PLAYER_H
