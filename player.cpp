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
    // emit player::sig_disp();
//传值
    list_name.empty();
    list_url.empty();
     const QString URLSTR = "http://music.163.com/api/playlist/detail?id=23075108";
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
            int i=0;
            foreach (QVariant plugin, nestedMap["tracks"].toList()) {
                QVariantMap music_info=plugin.toMap();
                //qDebug() << "mp3Url:" << test["mp3Url"].toString();
                    list_url.append(music_info["mp3Url"].toString());
                    list_name.append(music_info["name"].toString());
//                        strArray.append(music_info["mp3Url"].toString());
//                        strArray.append(music_info["name"].toString());
                       // qDebug()<<""<<i++;
            }

        }
    } else {
        qFatal(error.errorString().toUtf8().constData());
        exit(1);
    }

    //返回随机数据

        int ran_num=0;
        srand((unsigned)time(0));
            ran_num=rand()%list_url.size();
qDebug()<<"当前播放歌曲:"<<list_name[ran_num]<<"  链接:"<<list_url[ran_num];
    emit player::sig(list_url[ran_num]);
  //  emit player::sig("http://m2.music.126.net/M6SbDY4_KTTXy-XKVse8Jg==/7735064302565150.mp3");
  //  qDebug()<<"strArray_name size:"<<strArray_name.size();
}


player::~player()
{

}

QVector<QString>  player::json(){
   //QVector<QString>   array(len);//声明变长数组

    QVector<QString> strArray;
    list_name.empty();
    list_url.empty();

     const QString URLSTR = "http://music.163.com/api/playlist/detail?id=23075108";
    QString code="";
    //获取电台html
    QUrl url_(URLSTR);
      QNetworkAccessManager manager;
      QEventLoop loop;
      qDebug() << "Reading code form " << URLSTR;
      //发出请求
      QNetworkReply *reply = manager.get(QNetworkRequest(url_));
      //请求结束并下载完成后，退出子事件循环
      QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
      //开启子事件循环
      loop.exec();

      //将读到的信息写入文件
      code = reply->readAll();
      //返回随机数据

//        int ran_num;
//        srand((unsigned)time(0));
//            ran_num=rand()%list_url.count();

//解析json并添加
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(code.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (jsonDocument.isObject()) {
            QVariantMap result = jsonDocument.toVariant().toMap();
            QVariantMap nestedMap = result["result"].toMap();

            foreach (QVariant plugin, nestedMap["tracks"].toList()) {
                QVariantMap music_info=plugin.toMap();
                //qDebug() << "mp3Url:" << test["mp3Url"].toString();
//                    list_url.append(music_info["mp3Url"].toString());
//                    list_name.append(music_info["name"].toString());
                        strArray.append(music_info["mp3Url"].toString());
                        strArray.append(music_info["name"].toString());
                        qDebug()<<"test";
            }

        }
    } else {
        qFatal(error.errorString().toUtf8().constData());
        exit(1);
    }
    return strArray;
}
