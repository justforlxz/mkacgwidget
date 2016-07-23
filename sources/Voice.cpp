#include "headers/Voice.h"
#include "iostream"
#include <QObject>
Voice::Voice():m_baiduVop("pxxHWz9KmNsleFBsuWHQ77Hd", "b5a9a0eb50d410b0dccd3eec5fc30388") {
std::cout<<"构造函数运行了";
std::cout<< "Refresh token:" << m_baiduVop.refreshToken();
}

void Voice::inputFinish() {

    const auto &&data = m_baiduVop.finish();

    if(data.first) {
        emit Voice::sig(data.second);
        std::cout<<data.second.toStdString();
    } else {
        emit Voice::sig("识别错误");
    }
    std::cout<< "Refresh token:" << m_baiduVop.refreshToken();
}

void Voice::startInput() {
// m_baiduVop("pxxHWz9KmNsleFBsuWHQ77Hd", "b5a9a0eb50d410b0dccd3eec5fc30388");
     m_baiduVop.start();
}

Voice::~Voice() {

}
