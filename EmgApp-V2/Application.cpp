#include "Application.h"

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv),
      m_receiveThread(nullptr),
      m_recordThread(nullptr)
{

}

Application::~Application()
{
    shutThreadDown();
    setSettings();
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
    if (m_receiveThread) {
        m_receiveThread->quit();
        m_receiveThread->wait(2000);
        delete m_receiveThread;
        m_receiveThread = nullptr;
    }

    if (m_recordThread) {
        m_recordThread->quit();
        m_recordThread->wait(2000);
        delete m_recordThread;
        m_recordThread = nullptr;
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
    context.replotFreq  =  settings.value("replotfreq", 40).toInt();
    settings.endGroup();

    qDebug() << context.serverIp << context.serverPort << context.sampleCount << context.replotFreq;
}

void Application::setSettings()
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
