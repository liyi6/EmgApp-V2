#include "Logger.h"

Logger* Logger::m_instance = nullptr;

Logger::Logger(QObject *parent)
    : QObject(parent),
      m_logThread(nullptr)
{
    m_logThread = new LoggerThread();
    m_logThread->start();
}

Logger *Logger::instance()
{
    if (!m_instance) {
        m_instance = new Logger;
    }
    return m_instance;
}

void Logger::destroyInstance()
{
    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

Logger::~Logger()
{
    qDebug() << "~Logger() called.";

    if (m_logThread && m_logThread->isRunning()) {
        m_logThread->stop();
        m_logThread->wait(2000);

        if (m_logThread->isRunning()) {
            m_logThread->terminate();
        }

        delete m_logThread;
        m_logThread = nullptr;
    }
}

void Logger::log(QString msg, Logger::LogLeverl level)
{
    QString log;
    switch (level) {
    case Info:
        log += "[Info] ";
        break;
    case Warn:
        log += "[Warn] ";
        break;
    case Err:
        log += "[Erro] ";
        break;
    case Sys:
        log += "[Syst] ";
        break;
    }
    log += QDateTime::currentDateTime().toString("[yyyy-MM-dd-hh-mm-ss] ");
    log += msg;
    m_logThread->appendMsg(log);
}

LoggerThread::LoggerThread()
    : m_logFile(nullptr),
      m_stop(false)
{
    QDir logFileDir;
    logFileDir.mkpath(Utils::getAppHomeDir()+ "/logs/");
    QString logFilePath = QString(Utils::getAppHomeDir() + "/logs/" + "emg-%1").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + ".log");

    m_logFile = new QFile(logFilePath);
    if (!m_logFile->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qWarning() << "Fail to Open record file.";
        m_logFile = nullptr;
        return;
    }
}

LoggerThread::~LoggerThread()
{
    if (m_logFile && m_logFile->isOpen()) {
        m_logFile->close();
        delete m_logFile;
        m_logFile = nullptr;
    }
}

void LoggerThread::run()
{    
    QString msg;
    QTextStream outTream(m_logFile);
    while(!m_stop) {
        msg.clear();
        {
            QMutexLocker locker(&m_queMutex);
            if (!m_msgQue.isEmpty()) {
                msg = m_msgQue.takeFirst();
            }
        }
        if (!msg.isEmpty()) {
            outTream << msg << endl;
        }
        QThread::msleep(50);
    }
}

void LoggerThread::stop()
{
    m_stop = true;
}

void LoggerThread::appendMsg(QString &msg)
{
    QMutexLocker locker(&m_queMutex);
    m_msgQue.append(msg);
}
