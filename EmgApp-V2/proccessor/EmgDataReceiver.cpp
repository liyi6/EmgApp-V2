#include "EmgDataReceiver.h"

EmgDataReceiver* EmgDataReceiver::m_instance = nullptr;

EmgDataReceiver:: EmgDataReceiver(QObject *parent)
    : QObject(parent),
      m_socket(nullptr),
      m_headFind(false),
      m_curChennel(0),
      m_stop(true)
{
    // 初始化socket
    m_socket = new QTcpSocket(this);
    connect(m_socket, SIGNAL(connected()), this, SIGNAL(netConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onNetDisconect()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onNetError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));

    // 初始化每次接收的剩余数据
    m_dataLeft.clear();

    // 初始化每个通道的存储数据，以及相应的锁
    for (int channel=0; channel<CHANNEL_SIZE; channel++) {
        QVector<double>* dataVec = new QVector<double>;
        m_dataContainer.insert(channel, dataVec);

        QMutex* dataVecMutex = new QMutex;
        m_dataContainerMutex.append(dataVecMutex);
    }
}

void EmgDataReceiver::resetDataContainer()
{
    Context& context = AppContext::instance()->getContext();
    // 初始化每个纵轴点
    for (int channel=0; channel<CHANNEL_SIZE; channel++) {
        QVector<double>* dataVec = m_dataContainer.value(channel);
        dataVec->clear();
        for (int i=0; i<context.sampleCount; i++) {
            dataVec->append(0);
        }
    }

    // 初始化每个横轴点
    m_xAxisValue.clear();
    for (int i=0; i<context.sampleCount; i++) {
        m_xAxisValue.append(i);
    }

    // 初始化残留点
    m_dataLeft.clear();
}

EmgDataReceiver::~EmgDataReceiver()
{
    qDebug() << "~EmgDataReceiver() called.";

    if (m_socket && QAbstractSocket::UnconnectedState != m_socket->state()) {
        m_socket->close();
    }
}

EmgDataReceiver *EmgDataReceiver::instance()
{
    if (!m_instance) {
        m_instance = new EmgDataReceiver;
    }
    return m_instance;
}

void EmgDataReceiver::destroyInstance()
{
    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

void EmgDataReceiver::onConnectToHost()
{
    if (m_socket && QAbstractSocket::UnconnectedState == m_socket->state()) {
        Context& context = AppContext::instance()->getContext();
        qDebug() << "Try to connect to host(" << context.serverIp << ":" << context.serverPort << ")";
        m_socket->connectToHost(context.serverIp, context.serverPort);
    } else {
        qWarning() << "Socket state is not unconnected state, so will reject connecting operate.";
    }
}

void EmgDataReceiver::onSendStartCmd()
{
    if (m_socket && QAbstractSocket::ConnectedState == m_socket->state()) {
        Command cmd;
        cmd.header      = 0x5555AAAA;
        cmd.cmdType     = 0x00000001;
        m_socket->write(cmd.toByteArray());

        qDebug() << "Send start cmd.";

        m_stop = false;
    } else {
        qWarning() << "Fail to send start cmd because of disconnecting to server.";
    }

    resetDataContainer();
}

void EmgDataReceiver::onSendStopCmd()
{
    if (m_socket && QAbstractSocket::ConnectedState == m_socket->state()) {
        Command cmd;
        cmd.header      = 0x5555AAAA;
        cmd.cmdType     = 0x00000000;
        m_socket->write(cmd.toByteArray());

        qDebug() << "Send stop cmd.";

        m_stop = true;
    } else {
        qWarning() << "Fail to send stop cmd because of disconnecting to server.";
    }
}

void EmgDataReceiver::onNetError(QAbstractSocket::SocketError)
{
    m_headFind = false;
    emit netError();
}

void EmgDataReceiver::onNetDisconect()
{
    m_headFind = false;
}

void EmgDataReceiver::onReadReady()
{
    if (m_socket && m_socket->bytesAvailable()) {
        QByteArray data = m_socket->readAll();

        if (m_stop) {
            return;
        }

        if (!m_headFind) {     // 如果还未读到数据头
            int head = data[0] & 0x000000FF;
            head |= ((data[1] << 8) & 0x0000FF00);
            head |= ((data[2] << 16) & 0x00FF0000);
            head |= ((data[3] << 24) & 0xFF000000);
            if (0xAAAA5555 == head) {
                qDebug() << "Success to find head of data.";
                m_headFind = true;
                data.remove(0, 4);
                dataProcess(data);
            } else {
                qWarning() << "Head of data find failed, data will be bannished";
            }
        } else {
            dataProcess(data);
        }
    }
    QThread::usleep(100);
}

void EmgDataReceiver::dataProcess(QByteArray &data)
{
    emit orignalDataComming(data);  // 发送原始数据
    /**
     * channel数为16(0~15), 每个通道数据占2个Byte
     * 若某次传入的data的Byte数不为偶数时会有余留数据，需要保存到下次处理
     */

    if (m_dataLeft.size() > 0) {
        data.prepend(m_dataLeft);
    }

    while(data.size() > 1) {
        short channelData = data[0] & 0x000000FF;
        channelData |= ((data[1] << 8) & 0x0000FF00);
        QVector<double>* dataVec = m_dataContainer.value(m_curChennel);
        QMutex* dataVecMutex = m_dataContainerMutex.at(m_curChennel);
        {
            QMutexLocker locker(dataVecMutex);
            dataVec->append(channelData);
            dataVec->removeFirst();
        }
        m_curChennel = ++m_curChennel % CHANNEL_SIZE;
        data.remove(0,2);
    }

    if (data.size() == 1) {
        m_dataLeft = data;
    }

    //    /**
    //     * channel数为16(0~15), 每个通道数据占4个Byte
    //     * 若某次传入的data的Byte数不为4的倍数时会有余留数据，需要保存到下次处理
    //     */

    //    if (m_dataLeft.size() > 0) {
    //        data.prepend(m_dataLeft);
    //    }

    //    while(data.size() >= 4) {
    //        int channelData = data[0] & 0x000000FF;
    //        channelData |= ((data[1] << 8) & 0x0000FF00);
    //        channelData |= ((data[2] << 16) & 0x00FF0000);
    //        channelData |= ((data[3] << 24) & 0xFF000000);
    //        emit dataComming(m_curChennel, channelData);
    //        m_curChennel = ++m_curChennel % 16;
    //        data = data.mid(4);
    //        if (data.size() < 4 && data.size() > 0) {
    //            m_dataLeft = data;
    //        }
    //    }
}

void EmgDataReceiver::updateGraph(int channel, QPointer<QCPGraph> &graph)
{
    QVector<double>* dataVec = m_dataContainer.value(channel);
    QMutex*    dataVecMutex = m_dataContainerMutex.at(channel);
    {
        QMutexLocker locker(dataVecMutex);
        graph->setData(m_xAxisValue, *dataVec);
    }
}


