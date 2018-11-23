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

    qDebug() << "~EmgDataReceiver() called.";
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
            int head = data[0] & 0x000000FF;
            head |= ((data[1] << 8) & 0x0000FF00);
            head |= ((data[2] << 16) & 0x00FF0000);
            head |= ((data[3] << 24) & 0xFF000000);
            if (0xAAAA5555 == head) {
                qDebug() << "Success to find head of data.";
                m_headFind = true;
                data.remove(0, 4);
                dataProcessV2(data);
            } else {
                qWarning() << "Head of data find failed, data will be bannished";
            }
        } else {
            dataProcessV2(data);
        }
    }
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
        emit dataComming(m_curChennel, channelData);
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

void EmgDataReceiver::dataProcessV2(QByteArray &data)
{
    static QByteArray channel0Data;
    static QByteArray channel1Data;
    static QByteArray channel2Data;
    static QByteArray channel3Data;
    static QByteArray channel4Data;
    static QByteArray channel5Data;
    static QByteArray channel6Data;
    static QByteArray channel7Data;
    static QByteArray channel8Data;
    static QByteArray channel9Data;
    static QByteArray channel10Data;
    static QByteArray channel11Data;
    static QByteArray channel12Data;
    static QByteArray channel13Data;
    static QByteArray channel14Data;
    static QByteArray channel15Data;

    static int dataCounter = 20;

    emit orignalDataComming(data);  // 发送原始数据
    /**
     * channel数为16(0~15), 每个通道数据占2个Byte
     * 若某次传入的data的Byte数不为偶数时会有余留数据，需要保存到下次处理
     */

    if (m_dataLeft.size() > 0) {
        data.prepend(m_dataLeft);
    }

    while (data.size() > 1) {
        switch (m_curChennel) {
        case 0:{
            channel0Data.append(data[0]);
            channel0Data.append(data[1]);
            if (channel0Data.size() == dataCounter) {
                emit channel0DataComming(channel0Data);
                channel0Data.clear();
            }
            break;
        }
        case 1:{
            channel1Data.append(data[0]);
            channel1Data.append(data[1]);
            if (channel1Data.size() == dataCounter) {
                emit channel1DataComming(channel1Data);
                channel1Data.clear();
            }
            break;
        }
        case 2:{
            channel2Data.append(data[0]);
            channel2Data.append(data[1]);
            if (channel2Data.size() == dataCounter) {
                emit channel2DataComming(channel2Data);
                channel2Data.clear();
            }
            break;
        }
        case 3:{
            channel3Data.append(data[0]);
            channel3Data.append(data[1]);
            if (channel3Data.size() == dataCounter) {
                emit channel3DataComming(channel3Data);
                channel3Data.clear();
            }
            break;
        }
        case 4:{
            channel4Data.append(data[0]);
            channel4Data.append(data[1]);
            if (channel4Data.size() == dataCounter) {
                emit channel4DataComming(channel4Data);
                channel4Data.clear();
            }
            break;
        }
        case 5:{
            channel5Data.append(data[0]);
            channel5Data.append(data[1]);
            if (channel5Data.size() == dataCounter) {
                emit channel5DataComming(channel5Data);
                channel5Data.clear();
            }
            break;
        }
        case 6:{
            channel6Data.append(data[0]);
            channel6Data.append(data[1]);
            if (channel6Data.size() == dataCounter) {
                emit channel6DataComming(channel6Data);
                channel6Data.clear();
            }
            break;
        }
        case 7:{
            channel7Data.append(data[0]);
            channel7Data.append(data[1]);
            if (channel7Data.size() == dataCounter) {
                emit channel7DataComming(channel7Data);
                channel7Data.clear();
            }
            break;
        }
        case 8:{
            channel8Data.append(data[0]);
            channel8Data.append(data[1]);
            if (channel8Data.size() == dataCounter) {
                emit channel8DataComming(channel8Data);
                channel8Data.clear();
            }
            break;
        }
        case 9:{
            channel9Data.append(data[0]);
            channel9Data.append(data[1]);
            if (channel9Data.size() == dataCounter) {
                emit channel9DataComming(channel9Data);
                channel9Data.clear();
            }
            break;
        }
        case 10:{
            channel10Data.append(data[0]);
            channel10Data.append(data[1]);
            if (channel10Data.size() == dataCounter) {
                emit channel10DataComming(channel10Data);
                channel10Data.clear();
            }
            break;
        }
        case 11:{
            channel11Data.append(data[0]);
            channel11Data.append(data[1]);
            if (channel11Data.size() == dataCounter) {
                emit channel11DataComming(channel11Data);
                channel11Data.clear();
            }
            break;
        }
        case 12:{
            channel12Data.append(data[0]);
            channel12Data.append(data[1]);
            if (channel12Data.size() == dataCounter) {
                emit channel12DataComming(channel12Data);
                channel12Data.clear();
            }
            break;
        }
        case 13:{
            channel13Data.append(data[0]);
            channel13Data.append(data[1]);
            if (channel13Data.size() == dataCounter) {
                emit channel13DataComming(channel13Data);
                channel13Data.clear();
            }
            break;
        }
        case 14:{
            channel14Data.append(data[0]);
            channel14Data.append(data[1]);
            if (channel14Data.size() == dataCounter) {
                emit channel14DataComming(channel14Data);
                channel14Data.clear();
            }
            break;
        }
        case 15:{
            channel15Data.append(data[0]);
            channel15Data.append(data[1]);
            if (channel15Data.size() == dataCounter) {
                emit channel15DataComming(channel15Data);
                channel15Data.clear();
            }
            break;
        }
        default:
            break;
        }
        m_curChennel = ++m_curChennel % CHANNEL_SIZE;
        data.remove(0,2);
    }

    if (data.size() == 1) {
        m_dataLeft = data;
    }

}


