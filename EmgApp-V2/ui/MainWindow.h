#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include "QCustomPlot.h"
#include "Defines.h"
#include "PlotWidget.h"
#include "EmgDataReceiver.h"
#include "EmgDataRecorder.h"
#include "SettingDlg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum RunStatus {
        NotRunning,
        Running
    };

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void start();
    void stop();

protected:
    void mousePressEvent(QMouseEvent*);

private slots:
    void on_btnFsc_clicked();
    void on_btnStart_clicked();
    void on_btnMenu_clicked();

    void onShowPrePage();
    void onShowNextPage();

private:
    void updateUi();

private:
    Ui::MainWindow*  ui;


private:
    int            m_curPage;
    RunStatus      m_runStatus;
    SettingDlg*    m_settingDlg;
};

#endif // MAINWINDOW_H
