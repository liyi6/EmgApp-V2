#include "EmgDataReceiver.h"

EmgDataReceiver* EmgDataReceiver::m_instance = NULL;

EmgDataReceiver::EmgDataReceiver(QObject *parent)
    : QObject(parent),
      m_socket(NULL),
      m_curChennel(0),
      m_headFind(false)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, SIGNAL(connected()), this, SIGNAL(netConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(onNetDisconect()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onNetError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));

    m_dataLeft.clear();
}

EmgDataReceiver::~EmgDataReceiver()
{
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

void EmgDataReceiver::onConnectToHost()
{
    if (m_socket && QAbstractSocket::UnconnectedState == m_socket->state()) {
        m_socket->connectToHost(SERVER_IP, SERVER_PORT);
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

        qDebug() << "Send start cmd: " << cmd.toByteArray();
    } else {
        qWarning() << "Fail to send start cmd because of disconnecting to server.";
    }
}

void EmgDataReceiver::onSendStopCmd()
{
    if (m_socket && QAbstractSocket::ConnectedState == m_socket->state()) {
        Command cmd;
        cmd.header      = 0x5555AAAA;
        cmd.cmdType     = 0x00000000;
        m_socket->write(cmd.toByteArray());

        qDebug() << "Send stop cmd: " << cmd.toByteArray();
    } else {
        qWarning() << "Fail to send stop cmd because of disconnecting to server.";
    }
}

void EmgDataReceiver::onNetError(QAbstractSocket::SocketError sockError)
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
        if (!m_headFind) {     // 如果还未读到数据头
            int32_t head = data[0] & 0x000000FF;
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
}

void EmgDataReceiver::dataProcess(QByteArray &data)
{
    static int fec = 0;

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

        //emit dataComming(m_curChennel, channelData);
        if (++fec%5 == 0) {
            switch(m_curChennel) {
            case 0:
                emit channel0DataComming(channelData);
                break;
            case 1:
                emit channel1DataComming(channelData);
                break;
            case 2:
                emit channel2DataComming(channelData);
                break;
            case 3:
                emit channel3DataComming(channelData);
                break;
            case 4:
                emit channel4DataComming(channelData);
                break;
            case 5:
                emit channel5DataComming(channelData);
                break;
            case 6:
                emit channel6DataComming(channelData);
                break;
            case 7:
                emit channel7DataComming(channelData);
                break;
            case 8:
                emit channel8DataComming(channelData);
                break;
            case 9:
                emit channel9DataComming(channelData);
                break;
            case 10:
                emit channel10DataComming(channelData);
                break;
            case 11:
                emit channel11DataComming(channelData);
                break;
            case 12:
                emit channel12DataComming(channelData);
                break;
            case 13:
                emit channel13DataComming(channelData);
                break;
            case 14:
                emit channel14DataComming(channelData);
                break;
            case 15:
                emit channel15DataComming(channelData);
                break;
            default:
                break;
            }
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


