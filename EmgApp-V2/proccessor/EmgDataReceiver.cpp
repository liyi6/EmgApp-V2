#include "EmgDataReceiver.h"

EmgDataReceiver* EmgDataReceiver::m_instance = NULL;

EmgDataReceiver::EmgDataReceiver(QObject *parent)
    : QObject(parent),
      m_socket(NULL)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, SIGNAL(connected()), this, SIGNAL(netConnected()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onNetError(QAbstractSocket::SocketError)));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));
}

EmgDataReceiver *EmgDataReceiver::instance()
{
    if (!m_instance) {
        m_instance = new EmgDataReceiver;
    }
    return m_instance;
}

void EmgDataReceiver::onNetError(QAbstractSocket::SocketError sockError)
{

}

void EmgDataReceiver::onReadReady()
{

}



void EmgDataReceiver::connectToHost(QString ip, qint16 port)
{
    if (m_socket) {
        m_socket->connectToHost(ip, port);
    }
}


