#ifndef STARTDLG_H
#define STARTDLG_H

#include <QDialog>
#include <QPainter>
#include <QMessageBox>

#include "EmgDataReceiver.h"

namespace Ui {
class StartDlg;
}

class StartDlg : public QDialog
{
    Q_OBJECT

public:
    explicit StartDlg(QWidget *parent = nullptr);
    ~StartDlg();

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void onConnected();
    void onConnectError();

private:
    void updateUi();

private:
    Ui::StartDlg* ui;
};

#endif // STARTDLG_H
