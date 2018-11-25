#ifndef EMGDATARECEIVER_H
#define EMGDATARECEIVER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include "Defines.h"
#include "QCustomPlot.h"
#include "AppContext.h"

class EmgDataReceiver : public QObject
{
    Q_OBJECT
public:
    ~EmgDataReceiver();
    static EmgDataReceiver* instance();

    void updateGraph(int channel, QPointer<QCPGraph>& graph);

signals:
    void netConnected();
    void netError();
    void orignalDataComming(QByteArray data);

public slots:
    void onConnectToHost();
    void onSendStartCmd();
    void onSendStopCmd();

private slots:
    void onNetError(QAbstractSocket::SocketError);
    void onReadReady();
    void onNetDisconect();

private:
    explicit EmgDataReceiver(QObject *parent = nullptr);
    void resetDataContainer();
    void dataProcess(QByteArray& data);

private:
    static EmgDataReceiver* m_instance;
    QTcpSocket*   m_socket;           // Tcp通信socket
    bool          m_headFind;         // 是否找到数据头
    QByteArray    m_dataLeft;         // dataLeft为上次处理后的余留数据(当数据)
    int           m_curChennel;       // 当前通道
    bool          m_stop;             // 停止解析数据

    QVector<double>               m_xAxisValue;
    QHash<int, QVector<double>*>  m_dataContainer;
    QVector<QMutex*>              m_dataContainerMutex;


};

#endif // EMGDATARECEIVER_H
