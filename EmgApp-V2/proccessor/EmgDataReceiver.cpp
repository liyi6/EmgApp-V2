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
    static int fec = 10;

    static QVector<short> channel0DataList;
    static QVector<short> channel1DataList;
    static QVector<short> channel2DataList;
    static QVector<short> channel3DataList;
    static QVector<short> channel4DataList;
    static QVector<short> channel5DataList;
    static QVector<short> channel6DataList;
    static QVector<short> channel7DataList;
    static QVector<short> channel8DataList;
    static QVector<short> channel9DataList;
    static QVector<short> channel10DataList;
    static QVector<short> channel11DataList;
    static QVector<short> channel12DataList;
    static QVector<short> channel13DataList;
    static QVector<short> channel14DataList;
    static QVector<short> channel15DataList;

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

//        if (++fec%5 == 0) {
//            switch(m_curChennel) {
//            case 0:
//                emit channel0DataComming(channelData);
//                break;
//            case 1:
//                emit channel1DataComming(channelData);
//                break;
//            case 2:
//                emit channel2DataComming(channelData);
//                break;
//            case 3:
//                emit channel3DataComming(channelData);
//                break;
//            case 4:
//                emit channel4DataComming(channelData);
//                break;
//            case 5:
//                emit channel5DataComming(channelData);
//                break;
//            case 6:
//                emit channel6DataComming(channelData);
//                break;
//            case 7:
//                emit channel7DataComming(channelData);
//                break;
//            case 8:
//                emit channel8DataComming(channelData);
//                break;
//            case 9:
//                emit channel9DataComming(channelData);
//                break;
//            case 10:
//                emit channel10DataComming(channelData);
//                break;
//            case 11:
//                emit channel11DataComming(channelData);
//                break;
//            case 12:
//                emit channel12DataComming(channelData);
//                break;
//            case 13:
//                emit channel13DataComming(channelData);
//                break;
//            case 14:
//                emit channel14DataComming(channelData);
//                break;
//            case 15:
//                emit channel15DataComming(channelData);
//                break;
//            default:
//                break;
//            }
//        }


        switch(m_curChennel) {
        case 0:
            channel0DataList.append(channelData);
            if (channel0DataList.size() > fec) {
                emit channel0DataComming(channel0DataList);
                channel0DataList.clear();
            }
            break;
        case 1:
            channel1DataList.append(channelData);
            if (channel1DataList.size() > fec) {
                emit channel1DataComming(channel1DataList);
                channel1DataList.clear();
            }
            break;
        case 2:
            channel2DataList.append(channelData);
            if (channel2DataList.size() > fec) {
                emit channel2DataComming(channel2DataList);
                channel2DataList.clear();
            }
            break;
        case 3:
            channel3DataList.append(channelData);
            if (channel3DataList.size() > fec) {
                emit channel3DataComming(channel3DataList);
                channel3DataList.clear();
            }
            break;
        case 4:
            channel4DataList.append(channelData);
            if (channel4DataList.size() > fec) {
                emit channel4DataComming(channel4DataList);
                channel4DataList.clear();
            }
            break;
        case 5:
            channel5DataList.append(channelData);
            if (channel5DataList.size() > fec) {
                emit channel5DataComming(channel5DataList);
                channel5DataList.clear();
            }
            break;
        case 6:
            channel6DataList.append(channelData);
            if (channel6DataList.size() > fec) {
                emit channel6DataComming(channel6DataList);
                channel6DataList.clear();
            }
            break;
        case 7:
            channel7DataList.append(channelData);
            if (channel7DataList.size() > fec) {
                emit channel7DataComming(channel7DataList);
                channel7DataList.clear();
            }
            break;
        case 8:
            channel8DataList.append(channelData);
            if (channel8DataList.size() > fec) {
                emit channel8DataComming(channel8DataList);
                channel8DataList.clear();
            }
            break;
        case 9:
            channel9DataList.append(channelData);
            if (channel9DataList.size() > fec) {
                emit channel9DataComming(channel9DataList);
                channel9DataList.clear();
            }
            break;
        case 10:
            channel10DataList.append(channelData);
            if (channel10DataList.size() > fec) {
                emit channel10DataComming(channel10DataList);
                channel10DataList.clear();
            }
            break;
        case 11:
            channel11DataList.append(channelData);
            if (channel11DataList.size() > fec) {
                emit channel11DataComming(channel11DataList);
                channel11DataList.clear();
            }
            break;
        case 12:
            channel12DataList.append(channelData);
            if (channel12DataList.size() > fec) {
                emit channel12DataComming(channel12DataList);
                channel12DataList.clear();
            }
            break;
        case 13:
            channel13DataList.append(channelData);
            if (channel13DataList.size() > fec) {
                emit channel13DataComming(channel13DataList);
                channel13DataList.clear();
            }
            break;
        case 14:
            channel14DataList.append(channelData);
            if (channel14DataList.size() > fec) {
                emit channel14DataComming(channel14DataList);
                channel14DataList.clear();
            }
            break;
        case 15:
            channel15DataList.append(channelData);
            if (channel15DataList.size() > fec) {
                emit channel15DataComming(channel15DataList);
                channel15DataList.clear();
            }
            break;
        default:
            break;
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


