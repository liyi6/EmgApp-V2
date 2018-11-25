#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include <QDateTime>
#include <QDebug>
#include <QThread>
#include <QAtomicInt>
#include "Utils.h"

class LoggerThread;

class Logger : public QObject
{
    Q_OBJECT
public:
    enum LogLeverl {
        Info,
        Warn,
        Err,
        Sys
    };

public:
    static Logger* instance();
    static void destroyInstance();
    ~Logger();

    void log(QString msg, LogLeverl level=Info);

private:
    explicit Logger(QObject *parent = nullptr);

private:
    static Logger* m_instance;
    LoggerThread*  m_logThread;
};

class LoggerThread: public QThread
{
    Q_OBJECT

public:
    LoggerThread();
    ~LoggerThread();

    void run();
    void stop();
    void appendMsg(QString& msg);

private:
    QList<QString>         m_msgQue;
    QMutex                 m_queMutex;
    QFile*                 m_logFile;
    QAtomicInteger<bool>   m_stop;
};

#endif // LOGGER_H
