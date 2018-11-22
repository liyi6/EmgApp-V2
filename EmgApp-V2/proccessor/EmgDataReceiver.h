#ifndef EMGDATARECEIVER_H
#define EMGDATARECEIVER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

#include "Defines.h"

class EmgDataReceiver : public QObject
{
    Q_OBJECT
public:
    ~EmgDataReceiver();
    static EmgDataReceiver* instance();

signals:
    void netConnected();
    void netError();
    void orignalDataComming(QByteArray data);
    void dataComming(int channel, short data);

    void channel0DataComming(short data);
    void channel1DataComming(short data);
    void channel2DataComming(short data);
    void channel3DataComming(short data);
    void channel4DataComming(short data);
    void channel5DataComming(short data);
    void channel6DataComming(short data);
    void channel7DataComming(short data);
    void channel8DataComming(short data);
    void channel9DataComming(short data);
    void channel10DataComming(short data);
    void channel11DataComming(short data);
    void channel12DataComming(short data);
    void channel13DataComming(short data);
    void channel14DataComming(short data);
    void channel15DataComming(short data);

public slots:
    void onConnectToHost();
    void onSendStartCmd();
    void onSendStopCmd();

private slots:
    void onNetError(QAbstractSocket::SocketError);
    void onReadReady();
    void onNetDisconect();

private:
    explicit EmgDataReceiver(QObject *parent = 0);

private:
    void dataProcess(QByteArray& data);

private:
    static EmgDataReceiver* m_instance;

private:
    QTcpSocket*   m_socket;     // Tcp通信socket
    bool          m_headFind;   // 是否找到数据头
    QByteArray    m_dataLeft;   // dataLeft为上次处理后的余留数据(当数据)
    int           m_curChennel; // 当前通道
};

#endif // EMGDATARECEIVER_H
