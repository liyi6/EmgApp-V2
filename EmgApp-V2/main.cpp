#include "MainWindow.h"
#include "StartDlg.h"
#include "Application.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    Application a(argc, argv);

    a.initLog();
    a.initSettings();
    a.initThread();
    a.startBatchProcess();

    StartDlg dlg;
    MainWindow main;

    if (QDialog::Accepted == dlg.exec()) {
        main.show();
    } else {
        a.clean();
        return 0;
    }
    return a.exec();
}
