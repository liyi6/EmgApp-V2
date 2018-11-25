#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>
#include <QSettings>
#include <QString>
#include "EmgDataReceiver.h"
#include "EmgDataRecorder.h"
#include "Defines.h"
#include "Utils.h"
#include "AppContext.h"

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int &argc, char **argv);
    ~Application();

    void initThread();
    void shutThreadDown();
    void initSettings();
    void setSettings();

private:
    QThread*   m_receiveThread;
    QThread*   m_recordThread;
};

#endif // APPLICATION_H
