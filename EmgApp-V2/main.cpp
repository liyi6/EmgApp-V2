#include "MainWindow.h"
#include "StartDlg.h"
#include "EmgDataReceiver.h"
#include "EmgDataRecorder.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QThread* receiveThread = new QThread;
    EmgDataReceiver::instance()->moveToThread(receiveThread);
    receiveThread->start();

    QThread* recordThread = new QThread;
    EmgDataRecorder::instance()->moveToThread(recordThread);
    recordThread->start();

    StartDlg dlg;
    MainWindow main;
    if (QDialog::Accepted == dlg.exec()) {
        main.show();
    } else {
        receiveThread->quit();
        receiveThread->wait(2000);
        receiveThread = NULL;

        recordThread->quit();
        recordThread->wait(2000);
        recordThread = NULL;
        return 0;
    }
    return a.exec();
}
