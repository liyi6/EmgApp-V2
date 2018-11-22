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
    m_collectThread->start();

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
    if (m_plotTimer && !m_plotTimer->isActive()) {
        m_plotTimer->start(REPLOT_FREQ);
    }
}

void PlotArea::stop()
{
    if (m_plotTimer && m_plotTimer->isActive()) {
        m_plotTimer->stop();
    }
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
    if (m_channel!=channel) {
        return;
    }

    {
        QMutexLocker locker(&m_dataContainerMutex);
        m_dataContainer.append(data);
        m_dataContainer.removeFirst();
    }
}
