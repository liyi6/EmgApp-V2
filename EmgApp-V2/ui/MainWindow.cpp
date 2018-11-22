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

    for (int i=0; i<POINT_SHOW; i++) {
        m_xAxisValue.append(i);
    }

    for (int channel=0; channel<CHANNEL_SIZE; channel++) {
        // set data container
        QVector<double>* dataList = new QVector<double>();
        m_dataContainer.insert(channel, dataList);

        // set plot
        QString plotControlName = "channel" + QString::number(channel);
        QCustomPlot* plot = this->findChild<QCustomPlot*>(plotControlName);
        if (!plot) {
            qWarning() << "Find plot error: can't find~~~ " << plotControlName;
            continue;
        }
        plot->yAxis->setTickLabels(false);
        connect(plot->yAxis2, SIGNAL(rangeChanged(QCPRange)), plot->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
        plot->axisRect()->addAxis(QCPAxis::atRight);
        plot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags

        // create graphs:
        QPointer<QCPGraph> graph = plot->addGraph(plot->xAxis, plot->axisRect()->axis(QCPAxis::atRight, 0));
        graph->setPen(QPen(QColor(250, 120, 0)));
        m_graphList.append(graph);
    }

    connect(&m_dataTimer, SIGNAL(timeout()), this, SLOT(onDrawData3()));
    m_dataTimer.start(INTERVAL_SHOW);
}

void MainWindow::on_btnFsc_clicked()
{

}

void MainWindow::on_btnStart_clicked()
{
    connect(EmgDataReceiver::instance(), SIGNAL(orignalDataComming(QByteArray&)), EmgDataRecorder::instance(), SLOT(onOrignalDataComming(QByteArray&)), Qt::QueuedConnection);
    emit start();
}

void MainWindow::on_btnStop_clicked()
{
    disconnect(EmgDataReceiver::instance(), SIGNAL(orignalDataComming(QByteArray&)), EmgDataRecorder::instance(), SLOT(onOrignalDataComming(QByteArray&)));
    emit stop();
}

void MainWindow::onDrawData()
{

//    for (int channel=0; channel<CHANNEL_SIZE; channel++) {


//        // set plot
//        QString plotControlName = "channel" + QString::number(channel);
//        QCustomPlot* plot = this->findChild<QCustomPlot*>(plotControlName);
//        if (!plot) {
//            qWarning() << "Find plot error: can't find--- " << plotControlName;
//        }
//        QPointer<QCPGraph> graph = m_graphList.at(channel);

//        QVector<double>* dataList = m_dataContainer.value(channel);
//        if (dataList) {
//            if (dataList->size() > 0) {

//                while (dataList->size() > 0) {
//                    graph->addData(graph->dataCount(), dataList->takeFirst());
//                }

//                plot->xAxis->rescale();
//                graph->rescaleValueAxis(false, true);
//                plot->xAxis->setRange(plot->xAxis->range().upper, POINT_SHOW, Qt::AlignRight);
//                plot->replot();
//            }
//        } else {
//            qWarning() << "Channel" << channel << "'s dataList is null.";
//        }
//    }
}

void MainWindow::onDrawData3()
{
//    for (int channel=0; channel<CHANNEL_SIZE; channel++) {
//        // set plot
//        QString plotControlName = "channel" + QString::number(channel);
//        QCustomPlot* plot = this->findChild<QCustomPlot*>(plotControlName);
//        if (!plot) {
//            qWarning() << "Find plot error: can't find--- " << plotControlName;
//        }
//        QPointer<QCPGraph> graph = m_graphList.at(channel);

//        QVector<double>* dataList = m_dataContainer.value(channel);
//        if (dataList) {
//            if (dataList->size() > 0) {

//                if (dataList->size() > POINT_SHOW) {
//                    dataList->remove(0, dataList->size()-POINT_SHOW);
//                }

//                graph->setData(m_xAxisValue, *dataList);
//                //dataList->clear();

//                plot->xAxis->rescale();
//                graph->rescaleValueAxis(false, true);
//                plot->xAxis->setRange(plot->xAxis->range().upper, POINT_SHOW, Qt::AlignRight);
//                plot->replot();
//            }
//        } else {
//            qWarning() << "Channel" << channel << "'s dataList is null.";
//        }
//    }
}

//void MainWindow::onDrawData2()
//{
//    NetConnectHelper::instance()->getDataContainer(m_dataContainer);

//    static QTime time(QTime::currentTime());
//    // calculate two new data points:
//    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

//    for (int channel=0; channel<CHANNEL_SIZE; channel++) {
//        // set plot
//        QString plotControlName = "channel" + QString::number(channel);
//        QCustomPlot* plot = this->findChild<QCustomPlot*>(plotControlName);
//        if (!plot) {
//            qWarning() << "Find plot error: can't find--- " << plotControlName;
//        }
//        QPointer<QCPGraph> graph = m_graphList.at(channel);

//        QVector<double>* dataList = m_dataContainer.value(channel);
//        if (dataList) {
//            if (dataList->size() > 0) {

//                graph->addData(key, dataList->takeFirst());
//                dataList->clear();

//                plot->xAxis->rescale();
//                graph->rescaleValueAxis(false, true);
//                plot->xAxis->setRange(key, 8, Qt::AlignRight);
//                plot->replot();
//            }
//        } else {
//            qWarning() << "Channel" << channel << "'s dataList is null.";
//        }
//    }
//}


