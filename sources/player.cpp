#include "headers/player.h"
#include "QQuickView"
#include "QQmlContext"
#include "headers/Voice.h"
#include "QTime"
Player::Player() {
    viwer.setFlags(Qt::FramelessWindowHint);
    viwer.setColor(QColor(Qt::transparent));
    viwer.setSource(QUrl("qrc:/main.qml"));

}
void Player::show() {
    viwer.show();
    viwer.rootContext()->setContextProperty("mainwindow",&viwer);
    QObject *playerObject=viwer.rootObject();
    Voice *_voice=new Voice();
//设置电台
    QObject::connect(playerObject,SIGNAL(next()),\
                     this,SLOT(slot_hex2dec()));
    QObject::connect(this,SIGNAL(sig(QVariant)),\
                     playerObject,SLOT(loaded_play(QVariant)));
//设置语音
//    QObject::connect(playerObject,SIGNAL(voice_start()),\
//                     _voice,SLOT(test1()));
    QObject::connect(_voice,SIGNAL(start()),
                     _voice,SLOT(startInput()));
    QObject::connect(_voice,SIGNAL(end()),
                     _voice,SLOT(inputFinish()));
    QObject::connect(playerObject,SIGNAL(voice_end()),\
                     _voice,SLOT(inputFinish()));

    QObject::connect(_voice,SIGNAL(sig(QVariant)),\
                     playerObject,SLOT(show_text(QVariant)));
//一言
    QObject::connect(playerObject,SIGNAL(hitokoto()),\
                     this,SLOT(slot_hitokoto()));

    QObject::connect(this,SIGNAL(sig_hitokoto(QVariant)),\
                     playerObject,SLOT(get_hitokoto(QVariant)));
}
void Player::setXY(float hajimeX, float hajimeY) {
    viwer.setX(hajimeX);
    viwer.setY(hajimeY);
}

void Player::slot_hex2dec() {
//传值
    list_name.empty();
    list_url.empty();
    const QString URLSTR = "http://music.163.com/api/playlist/detail?id=382664334";
    QString code="";
//获取电台html
    QUrl url(URLSTR);
    QNetworkAccessManager manager;
    QEventLoop loop;
    qDebug() << "Reading code form " << URLSTR;
//发出请求
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
//请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
//开启子事件循环
    loop.exec();
//将读到的信息写入文件
    code = reply->readAll();
//解析json并添加
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(code.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject()) {
            QVariantMap result = jsonDocument.toVariant().toMap();
            QVariantMap nestedMap = result["result"].toMap();
            //int i=0;
            foreach (QVariant plugin, nestedMap["tracks"].toList()) {
                QVariantMap music_info=plugin.toMap();
                    list_url.append(music_info["mp3Url"].toString());
                    list_name.append(music_info["name"].toString());
            }
        }
    } else {
        qFatal(error.errorString().toUtf8().constData());
        exit(1);
    }

//返回随机数据
    int ran_num=0;

    ran_num=rand()%list_url.size();
    qDebug()<<"当前播放歌曲:"<<list_name[ran_num]<<"  链接:"<<list_url[ran_num];
    emit Player::sig(list_url[ran_num]);
}


Player::~Player() {

}
void Player::slot_hitokoto() {
//处理html代码并返回
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl("https://api.lwl12.com/hitokoto/main/get")));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString html = response->readAll(); // Source should be stored here
    qDebug()<<html;
    emit Player::sig_hitokoto(html);
}
