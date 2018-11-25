#include "Application.h"

static void LogHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context)
    if (msg.startsWith("libpng")) {
        return;
    }
    Logger::LogLeverl level;
    switch (type) {
    case QtWarningMsg:
        level = Logger::Warn;
        break;
    case QtFatalMsg:
        level = Logger::Err;
        break;
    case QtSystemMsg:
        level = Logger::Sys;
        break;
    default:
        level = Logger::Info;
        break;
    };
    //QString logMsg = QString("[%1] [%2] [%3] %4").arg(context.file).arg(QString(context.function)).arg(QString(context.line)).arg(msg);

    QString logMsg = msg;
    Logger::instance()->log(logMsg, level);
}

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv),
      m_receiveThread(nullptr),
      m_recordThread(nullptr),
      m_batchProcess(nullptr)
{

}

Application::~Application()
{
    clean();
}

void Application::startBatchProcess()
{
    m_batchProcess = new QProcess;
    connect(m_batchProcess, SIGNAL(readyReadStandardError()), this, SLOT(onBatchProcessInfo()));
    m_batchProcess->start("venus_run.bat");
}

void Application::onBatchProcessInfo()
{
    if (m_batchProcess) {
        QString info = QString::fromLocal8Bit(m_batchProcess->readAllStandardOutput());
        Logger::instance()->log(info);

        QString err = QString::fromLocal8Bit(m_batchProcess->readAllStandardError());
        Logger::instance()->log(err, Logger::Err);
    }
}

void Application::initLog()
{
    qInstallMessageHandler(LogHandler);
}

void Application::initThread()
{
    m_receiveThread = new QThread;
    EmgDataReceiver::instance()->moveToThread(m_receiveThread);
    m_receiveThread->start();

    m_recordThread = new QThread;
    EmgDataRecorder::instance()->moveToThread(m_recordThread);
    m_recordThread->start();
}

void Application::shutThreadDown()
{
    if (m_receiveThread && m_receiveThread->isRunning()) {
        m_receiveThread->quit();
        m_receiveThread->wait(2000);
        delete m_receiveThread;
        m_receiveThread = nullptr;
    }

    if (m_recordThread && m_recordThread->isRunning()) {
        m_recordThread->quit();
        m_recordThread->wait(2000);
        delete m_recordThread;
        m_recordThread = nullptr;
    }

    if(m_batchProcess && m_batchProcess->state() != QProcess::NotRunning) {
        m_batchProcess->kill();
        m_batchProcess->waitForFinished();
        delete m_batchProcess;
        m_batchProcess = nullptr;
    }
}

void Application::initSettings()
{
    QDir settingsFileDir;
    settingsFileDir.mkpath(Utils::getAppHomeDir());
    QString settingsFilePath = QString(Utils::getAppHomeDir() + "/settings.ini");

    Context& context = AppContext::instance()->getContext();

    QSettings settings(settingsFilePath, QSettings::IniFormat);
    settings.beginGroup("Server");
    context.serverIp    =  settings.value("serverip", "localhost").toString();
    context.serverPort  =  quint16(settings.value("serverport", 4000).toInt());
    settings.endGroup();
    settings.beginGroup("Plot");
    context.sampleCount =  settings.value("samplecount", 2400).toInt();
    if (context.sampleCount < MIN_SAMPLE_COUNT || context.sampleCount > MAX_SAMPLE_COUNT) {
        qWarning() << "Sample count greater than max value(2400*4)! Sample count will be set to def value 2400.";
        context.sampleCount = DEF_SAMPLE_COUNT;
    }
    context.replotFreq  =  settings.value("replotfreq", 40).toInt();
    if (context.replotFreq < MIN_REPLOT_FREQ || context.replotFreq > MAX_REPLOT_FREQ) {
        qWarning() << "Sample count greater than max value(2400*4)! Sample count will be set to max value.";
        context.replotFreq = DEF_REPLOT_FREQ;
    }
    settings.endGroup();

    qDebug() << context.serverIp << context.serverPort << context.sampleCount << context.replotFreq;
}

void Application::saveSettings()
{
    QDir settingsFileDir;
    settingsFileDir.mkpath(Utils::getAppHomeDir());
    QString settingsFilePath = QString(Utils::getAppHomeDir() + "/settings.ini");

    Context& context = AppContext::instance()->getContext();

    QSettings settings(settingsFilePath, QSettings::IniFormat);
    settings.beginGroup("Server");
    settings.setValue("serverip", context.serverIp);
    settings.setValue("serverport", context.serverPort);
    settings.endGroup();
    settings.beginGroup("Plot");
    settings.setValue("samplecount", context.sampleCount);
    settings.setValue("replotfreq", context.replotFreq);
    settings.endGroup();
}

void Application::destroySingleObject()
{
    EmgDataRecorder::destroyInstance();
    EmgDataReceiver::destroyInstance();
    //AppContext::destroyInstance();
    Logger::destroyInstance();
}

void Application::clean()
{
    saveSettings();
    shutThreadDown();
    destroySingleObject();
}


