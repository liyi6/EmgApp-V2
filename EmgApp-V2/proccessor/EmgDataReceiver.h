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
    void netError(QAbstractSocket::SocketError);
    void orignalDataComming(QByteArray& data);
    void dataComming(int channel, short data);

public slots:
    void onConnectToHost();
    void onSendStartCmd();
    void onSendStopCmd();

private:
    explicit EmgDataReceiver(QObject *parent = 0);


private slots:
    void onNetError(QAbstractSocket::SocketError);
    void onReadReady();
    void onNetDisconect();

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
