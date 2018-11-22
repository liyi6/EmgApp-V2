#include "MainWindow.h"
#include "StartDlg.h"
#include "EmgDataReceiver.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QThread* workerThread = new QThread;
    EmgDataReceiver::instance()->moveToThread(workerThread);
    workerThread->start();

    StartDlg dlg;
    MainWindow main;
    if (QDialog::Accepted == dlg.exec()) {
        main.show();
    } else {
        return 0;
    }

    workerThread->quit();
    workerThread->wait(2000);

    return a.exec();
}
