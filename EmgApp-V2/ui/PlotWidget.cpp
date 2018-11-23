#include "PlotWidget.h"

PlotWidget::PlotWidget(QWidget *parent)
    : QCustomPlot(parent),
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

    m_plotTimer = new QTimer(this);
    connect(m_plotTimer, SIGNAL(timeout()), this, SLOT(onReplot()));
}

void PlotWidget::start()
{
    if (m_plotTimer && !m_plotTimer->isActive()) {
        m_plotTimer->start(REPLOT_FREQ);
    }
}

void PlotWidget::stop()
{
    if (m_plotTimer && m_plotTimer->isActive()) {
        m_plotTimer->stop();
    }
}

void PlotWidget::setChannel(int channel)
{
    m_channel = channel;
}

void PlotWidget::onReplot()
{
    EmgDataReceiver::instance()->updateGraph(m_channel, m_graph);
    this->xAxis->rescale();
    m_graph->rescaleValueAxis(false, true);
    this->xAxis->setRange(this->xAxis->range().upper, X_AXIS_POINS, Qt::AlignRight);
    this->replot();
}
