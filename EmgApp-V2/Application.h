#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>
#include <QSettings>
#include <QString>
#include <QProcess>
#include "EmgDataReceiver.h"
#include "EmgDataRecorder.h"
#include "Defines.h"
#include "Utils.h"
#include "AppContext.h"
#include "Logger.h"

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int &argc, char **argv);
    ~Application();

    void startBatchProcess();
    void initLog();
    void initThread();
    void initSettings();
    void clean();

private slots:
    void onBatchProcessInfo();

private:
    void shutThreadDown();
    void saveSettings();
    void destroySingleObject();

private:
    QThread*   m_receiveThread;
    QThread*   m_recordThread;
    QProcess*  m_batchProcess;
};

#endif // APPLICATION_H
