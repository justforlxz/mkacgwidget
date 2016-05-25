#include "Voice.h"
Voice::Voice():m_baiduVop("pxxHWz9KmNsleFBsuWHQ77Hd", "b5a9a0eb50d410b0dccd3eec5fc30388"){

}

void Voice::inputFinish(){
    const auto &&data = m_baiduVop.finish();

    if(data.first)
    {
      //  m_ui->label->setText(data.second);
        emit Voice::sig(data.second);
    }
    else
    {
      //  m_ui->label->setText("识别错误");
        emit Voice::sig("识别错误");
    }
}

void Voice::startInput(){
   // m_baiduVop("pxxHWz9KmNsleFBsuWHQ77Hd", "b5a9a0eb50d410b0dccd3eec5fc30388");
     m_baiduVop.start();
    emit Voice::send_time();
}
