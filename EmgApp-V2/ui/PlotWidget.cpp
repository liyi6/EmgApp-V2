#include "PlotWidget.h"

PlotWidget::PlotWidget(QWidget *parent)
    : QCustomPlot(parent),
      m_plotTimer(nullptr),
      m_channel(-1)
{

    yAxis->setTickLabels(false);
    connect(this->yAxis2, SIGNAL(rangeChanged(QCPRange)), this->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    axisRect()->addAxis(QCPAxis::atRight);
    axisRect()->axis(QCPAxis::atRight, 0)->setPadding(10); // add some padding to have space for tags

    xAxis->setLabel("x Axis");
    yAxis->setLabel("y Axis");

    // create graphs:
    m_graph = this->addGraph(this->xAxis, this->axisRect()->axis(QCPAxis::atRight, 0));
    m_graph->setPen(QPen(QColor(0, 255, 255, 200)));
    //setBackground(QBrush(QColor(10,10,10,240)));

    m_plotTimer = new QTimer(this);
    connect(m_plotTimer, SIGNAL(timeout()), this, SLOT(onReplot()));
}

void PlotWidget::start()
{
    Context& context = AppContext::instance()->getContext();
    if (m_plotTimer && !m_plotTimer->isActive()) {
        m_plotTimer->start(context.replotFreq);
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

    plotLayout()->insertRow(0);
    QCPTextElement *title = new QCPTextElement(this, "Channel" + QString::number(m_channel), QFont("Microsoft Yahei", 17, QFont::Bold));
    plotLayout()->addElement(0, 0, title);
}

void PlotWidget::onReplot()
{
    Context& context = AppContext::instance()->getContext();
    EmgDataReceiver::instance()->updateGraph(m_channel, m_graph);
    this->xAxis->rescale();
    m_graph->rescaleValueAxis(false, true);
    this->xAxis->setRange(this->xAxis->range().upper, context.sampleCount, Qt::AlignRight);
    this->replot();
}
