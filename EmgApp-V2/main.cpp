#include "MainWindow.h"
#include "StartDlg.h"
#include "Application.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    Application a(argc, argv);


    a.initSettings();
    a.initThread();

    StartDlg dlg;
    MainWindow main;

    if (QDialog::Accepted == dlg.exec()) {
        main.show();
    } else {
        a.shutThreadDown();
        return 0;
    }
    return a.exec();
}
