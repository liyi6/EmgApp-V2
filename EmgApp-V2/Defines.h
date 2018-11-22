﻿#ifndef DEFINES_H
#define DEFINES_H

#include <QByteArray>

#define   SERVER_IP      ( "localhost" )   // 服务器地址
#define   SERVER_PORT           ( 4000 )   // 服务器端口
#define   CHANNEL_SIZE            ( 16 )   // 通道数
#define   X_AXIS_POINS        ( 2400/2 )   // 横轴显示点数
#define   REPLOT_FREQ             ( 40 )   // 刷新界面频率

struct Command {
    int header;
    int cmdType;


    QByteArray toByteArray(){
        QByteArray abyte;
        abyte.resize(4);
        abyte[0] = (uchar)  (0x000000ff & header);
        abyte[1] = (uchar) ((0x0000ff00 & header) >> 8);
        abyte[2] = (uchar) ((0x00ff0000 & header) >> 16);
        abyte[3] = (uchar) ((0xff000000 & header) >> 24);
        abyte[4] = (uchar)  (0x000000ff & cmdType);
        abyte[5] = (uchar) ((0x0000ff00 & cmdType) >> 8);
        abyte[6] = (uchar) ((0x00ff0000 & cmdType) >> 16);
        abyte[7] = (uchar) ((0xff000000 & cmdType) >> 24);
        return abyte;
    }
};

struct EmgData {
    int raw;
    short env;
    short fft;
};

#endif // DEFINES_H
