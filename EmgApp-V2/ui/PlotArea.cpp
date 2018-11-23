#include "PlotArea.h"

PlotArea::PlotArea(QWidget *parent)
    : QCustomPlot(parent),
      m_collector(NULL),
      m_collectThread(NULL),
      m_plotTimer(NULL),
      m_channel(-1)
{
    this->yAxis->setTickLabels(false);
    connect(this->yAxis2, SIGNAL(rangeChanged(QCPRange)), this->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    this->axisRect()->addAxis(QCPAxis::atRight);
    this->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    m_graph = this->addGraph(this->xAxis, this->axisRect()->axis(QCPAxis::atRight, 0));
    m_graph->setPen(QPen(QColor(250, 120, 0)));

    m_collector = new DataCollector;
    m_collectThread = new QThread(this);
    m_collector->moveToThread(m_collectThread);

    m_plotTimer = new QTimer(this);
    connect(m_plotTimer, SIGNAL(timeout()), this, SLOT(onReplot()));
}

void PlotArea::setChannel(int channel)
{
    m_channel = channel;

    if (m_collector) {
        m_collector->setChannel(m_channel);
    }
}

void PlotArea::start()
{
    switch(m_channel) {
    case 0:
        connect(EmgDataReceiver::instance(), SIGNAL(channel0DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 1:
        connect(EmgDataReceiver::instance(), SIGNAL(channel1DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 2:
        connect(EmgDataReceiver::instance(), SIGNAL(channel2DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 3:
        connect(EmgDataReceiver::instance(), SIGNAL(channel3DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 4:
        connect(EmgDataReceiver::instance(), SIGNAL(channel4DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 5:
        connect(EmgDataReceiver::instance(), SIGNAL(channel5DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 6:
        connect(EmgDataReceiver::instance(), SIGNAL(channel6DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 7:
        connect(EmgDataReceiver::instance(), SIGNAL(channel7DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 8:
        connect(EmgDataReceiver::instance(), SIGNAL(channel8DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 9:
        connect(EmgDataReceiver::instance(), SIGNAL(channel9DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 10:
        connect(EmgDataReceiver::instance(), SIGNAL(channel10DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 11:
        connect(EmgDataReceiver::instance(), SIGNAL(channel11DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 12:
        connect(EmgDataReceiver::instance(), SIGNAL(channel12DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 13:
        connect(EmgDataReceiver::instance(), SIGNAL(channel13DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 14:
        connect(EmgDataReceiver::instance(), SIGNAL(channel14DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 15:
        connect(EmgDataReceiver::instance(), SIGNAL(channel15DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    default:
        break;
    }

    switch(m_channel) {
    case 0:
        connect(EmgDataReceiver::instance(), SIGNAL(channel0DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 1:
        connect(EmgDataReceiver::instance(), SIGNAL(channel1DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 2:
        connect(EmgDataReceiver::instance(), SIGNAL(channel2DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 3:
        connect(EmgDataReceiver::instance(), SIGNAL(channel3DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 4:
        connect(EmgDataReceiver::instance(), SIGNAL(channel4DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 5:
        connect(EmgDataReceiver::instance(), SIGNAL(channel5DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 6:
        connect(EmgDataReceiver::instance(), SIGNAL(channel6DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 7:
        connect(EmgDataReceiver::instance(), SIGNAL(channel7DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 8:
        connect(EmgDataReceiver::instance(), SIGNAL(channel8DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 9:
        connect(EmgDataReceiver::instance(), SIGNAL(channel9DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 10:
        connect(EmgDataReceiver::instance(), SIGNAL(channel10DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 11:
        connect(EmgDataReceiver::instance(), SIGNAL(channel11DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 12:
        connect(EmgDataReceiver::instance(), SIGNAL(channel12DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 13:
        connect(EmgDataReceiver::instance(), SIGNAL(channel13DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 14:
        connect(EmgDataReceiver::instance(), SIGNAL(channel14DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 15:
        connect(EmgDataReceiver::instance(), SIGNAL(channel15DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    default:
        break;
    }


    m_collectThread->start();

    if (m_plotTimer && !m_plotTimer->isActive()) {
        m_plotTimer->start(REPLOT_FREQ);
    }
}

void PlotArea::stop()
{
    if (m_plotTimer && m_plotTimer->isActive()) {
        m_plotTimer->stop();
    }

    m_collectThread->quit();
    m_collectThread->wait(2000);


    switch(m_channel) {
    case 0:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel0DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 1:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel1DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 2:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel2DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 3:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel3DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 4:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel4DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 5:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel5DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 6:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel6DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 7:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel7DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 8:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel8DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 9:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel9DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 10:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel10DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 11:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel11DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 12:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel12DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 13:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel13DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 14:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel14DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    case 15:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel15DataComming(short)), m_collector, SLOT(onDataComming(short)));
        break;
    default:
        break;
    }

    switch(m_channel) {
    case 0:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel0DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 1:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel1DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 2:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel2DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 3:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel3DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 4:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel4DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 5:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel5DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 6:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel6DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 7:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel7DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 8:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel8DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 9:
        connect(EmgDataReceiver::instance(), SIGNAL(channel9DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 10:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel10DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 11:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel11DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 12:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel12DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 13:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel13DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 14:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel14DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    case 15:
        disconnect(EmgDataReceiver::instance(), SIGNAL(channel15DataComming(QVector<short>)), m_collector, SLOT(onDataComming(QVector<short>)));
        break;
    default:
        break;
    }

    //disconnect(EmgDataReceiver::instance(), SIGNAL(dataComming(int, short)), m_collector, SLOT(onDataComming(int, short)));
}

void PlotArea::onReplot()
{
    m_collector->updateGraph(m_graph);
    this->xAxis->rescale();
    m_graph->rescaleValueAxis(false, true);
    this->xAxis->setRange(this->xAxis->range().upper, X_AXIS_POINS, Qt::AlignRight);
    this->replot();
}

DataCollector::DataCollector( QObject *parent)
    : QObject(parent),
      m_channel(-1)
{
    m_dataContainer.clear();
    for (int i=0; i<X_AXIS_POINS; i++) {
        m_dataContainer.append(0);
        m_xAxisValue.append(i);
    }
}

void DataCollector::setChannel(int channel)
{
    m_channel = channel;
}

void DataCollector::updateGraph(QPointer<QCPGraph> &graph)
{
    QMutexLocker locker(&m_dataContainerMutex);
    graph->setData(m_xAxisValue, m_dataContainer);
}

void DataCollector::onDataComming(int channel, short data)
{
    if (m_channel !=channel) {
        return;
    }

    {
        QMutexLocker locker(&m_dataContainerMutex);
        m_dataContainer.append(data);
        m_dataContainer.removeFirst();
    }
}

void DataCollector::onDataComming(short data)
{
    {
        QMutexLocker locker(&m_dataContainerMutex);
        m_dataContainer.append(data);
        m_dataContainer.removeFirst();
    }
}

void DataCollector::onDataComming(QVector<short> dataList)
{
    {
        QMutexLocker locker(&m_dataContainerMutex);
        for (int i; i<dataList.size(); i++) {
            m_dataContainer.append(dataList.at(i));
            m_dataContainer.removeFirst();
        }
    }
}
