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

    void channel0DataComming(QByteArray data);
    void channel1DataComming(QByteArray data);
    void channel2DataComming(QByteArray data);
    void channel3DataComming(QByteArray data);
    void channel4DataComming(QByteArray data);
    void channel5DataComming(QByteArray data);
    void channel6DataComming(QByteArray data);
    void channel7DataComming(QByteArray data);
    void channel8DataComming(QByteArray data);
    void channel9DataComming(QByteArray data);
    void channel10DataComming(QByteArray data);
    void channel11DataComming(QByteArray data);
    void channel12DataComming(QByteArray data);
    void channel13DataComming(QByteArray data);
    void channel14DataComming(QByteArray data);
    void channel15DataComming(QByteArray data);

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
    void dataProcessV2(QByteArray &data);

private:
    static EmgDataReceiver* m_instance;

private:
    QTcpSocket*   m_socket;     // Tcp通信socket
    bool          m_headFind;   // 是否找到数据头
    QByteArray    m_dataLeft;   // dataLeft为上次处理后的余留数据(当数据)
    int           m_curChennel; // 当前通道
};

#endif // EMGDATARECEIVER_H
