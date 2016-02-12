#include "player.h"

class playerData : public QSharedData
{
public:

};

player::player() : data(new playerData)
{

}



player &player::operator=(const player &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

void player::slot_hex2dec()
{
    QString url="http://m2.music.126.net/M6SbDY4_KTTXy-XKVse8Jg==/7735064302565150.mp3";
     emit player::sig_disp();
}

player::~player()
{

}
