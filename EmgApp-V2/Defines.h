#ifndef DEFINES_H
#define DEFINES_H

#include <QByteArray>
#include <QString>

#define   CHANNEL_SIZE               ( 16 )    // 通道数
#define   PAGE_COUNT                  ( 4 )    // 16通道分4页显示
#define   MAX_SAMPLE_COUNT       ( 2400*4 )    // 最大显示点数
#define   MIN_SAMPLE_COUNT         ( 1000 )    // 最小显示点数
#define   DEF_SAMPLE_COUNT         ( 2400 )    // 默认刷新点数
#define   MIN_REPLOT_FREQ           ( 300 )    // 最慢刷新速度300ms/次
#define   MAX_REPLOT_FREQ            ( 10 )    // 最快刷新速度10ms/次
#define   DEF_REPLOT_FREQ            ( 40 )    // 默认刷新速度40ms/次

struct Context {
    int      replotFreq;
    int     sampleCount;
    QString    serverIp;
    quint16  serverPort;
};

struct Command {
    int header;
    int cmdType;

    QByteArray toByteArray(){
        QByteArray abyte;
        abyte.resize(4);
        abyte[0] = (uchar)(0x000000ff & header);
        abyte[1] = (uchar)((0x0000ff00 & header) >> 8);
        abyte[2] = (uchar)((0x00ff0000 & header) >> 16);
        abyte[3] = (uchar)((0xff000000 & header) >> 24);

        abyte[4] = (uchar)(0x000000ff & cmdType);
        abyte[5] = (uchar)((0x0000ff00 & cmdType) >> 8);
        abyte[6] = (uchar)((0x00ff0000 & cmdType) >> 16);
        abyte[7] = (uchar)((0xff000000 & cmdType) >> 24);
        return abyte;
    }
};

struct EmgData {
    int raw;
    short env;
    short fft;
};




#endif // DEFINES_H
