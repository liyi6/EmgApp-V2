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
    explicit StartDlg(QWidget *parent = 0);
    ~StartDlg();

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void onConnected();
    void onConnectError(QAbstractSocket::SocketError sockError);

private:
    void updateUi();

private:
    Ui::StartDlg* ui;
};

#endif // STARTDLG_H
