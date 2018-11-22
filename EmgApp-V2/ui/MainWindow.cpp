#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateUi();

    connect(this, SIGNAL(start()), EmgDataRecorder::instance(), SLOT(onStartRecord()), Qt::QueuedConnection);
    connect(this, SIGNAL(start()), EmgDataReceiver::instance(), SLOT(onSendStartCmd()), Qt::QueuedConnection);

    connect(this, SIGNAL(stop()), EmgDataRecorder::instance(), SLOT(onStopRecord()), Qt::QueuedConnection);
    connect(this, SIGNAL(stop()), EmgDataReceiver::instance(), SLOT(onSendStopCmd()), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUi()
{
    setWindowIcon(QIcon("res/logo.ico"));
    setWindowTitle("EMG Demo");

    for (int channel=0; channel<CHANNEL_SIZE; channel++) {
        // set plot channel
        QString plotControlName = "channel" + QString::number(channel);
        PlotArea* plot = this->findChild<PlotArea*>(plotControlName);
        if (!plot) {
            qWarning() << "Find plot error: can't find~~~ " << plotControlName;
            continue;
        }
        plot->setChannel(channel);
    }
}

void MainWindow::on_btnFsc_clicked()
{

}

void MainWindow::on_btnStart_clicked()
{
    connect(EmgDataReceiver::instance(), SIGNAL(orignalDataComming(QByteArray)), EmgDataRecorder::instance(), SLOT(onOrignalDataComming(QByteArray)), Qt::QueuedConnection);
    emit start();

    for (int channel=0; channel<CHANNEL_SIZE; channel++) {
        // set plot channel
        QString plotControlName = "channel" + QString::number(channel);
        PlotArea* plot = this->findChild<PlotArea*>(plotControlName);
        if (!plot) {
            qWarning() << "Find plot error: can't find~~~ " << plotControlName;
            continue;
        }

        if (channel < 4){
            plot->start();
        }
    }
}

void MainWindow::on_btnStop_clicked()
{
    disconnect(EmgDataReceiver::instance(), SIGNAL(orignalDataComming(QByteArray)), EmgDataRecorder::instance(), SLOT(onOrignalDataComming(QByteArray)));
    emit stop();


    for (int channel=0; channel<CHANNEL_SIZE; channel++) {
        // set plot channel
        QString plotControlName = "channel" + QString::number(channel);
        PlotArea* plot = this->findChild<PlotArea*>(plotControlName);
        if (!plot) {
            qWarning() << "Find plot error: can't find~~~ " << plotControlName;
            continue;
        }

        if (channel < 4){
            plot->stop();
        }
    }
}




