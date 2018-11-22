#ifndef EMGDATARECEIVER_H
#define EMGDATARECEIVER_H

#include <QObject>
#include <QTcpSocket>

class EmgDataReceiver : public QObject
{
    Q_OBJECT
public:
    static EmgDataReceiver* instance();

public:
    void connectToHost(QString ip, qint16 port);

signals:
    void netConnected();

private:
    explicit EmgDataReceiver(QObject *parent = 0);

private slots:
    void onNetError(QAbstractSocket::SocketError);
    void onReadReady();

private:
    static EmgDataReceiver* m_instance;

private:
    QTcpSocket*      m_socket;     // Tcp通信socket
    bool             m_headFind;   // 是否找到数据头


public slots:
};

#endif // EMGDATARECEIVER_H
