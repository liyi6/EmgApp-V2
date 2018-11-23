#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include "QCustomPlot.h"
#include "Defines.h"
#include "PlotArea.h"
#include "PlotWidget.h"
#include "EmgDataReceiver.h"
#include "EmgDataRecorder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void start();
    void stop();

private slots:
    void on_btnFsc_clicked();
    void on_btnStart_clicked();
    void on_btnStop_clicked();

private:
    void updateUi();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
