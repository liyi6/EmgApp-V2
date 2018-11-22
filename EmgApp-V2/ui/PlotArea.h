#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QThread>
#include <QWidget>
#include <QVector>
#include <QPointer>
#include "QCustomPlot.h"
#include "Defines.h"

class DataCollector;

class PlotArea : public QCustomPlot
{
    Q_OBJECT
public:
    explicit PlotArea(QWidget *parent = 0);

    void start();
    void stop();
    void setChannel(int channel);

private slots:
    void onReplot();

private:
    DataCollector*   m_collector;      // 数据收集器
    QThread*         m_collectThread;  // 数据收集线程
    QTimer*          m_plotTimer;      // 刷新定时器
    int              m_channel;        // 绘制通道
    QPointer<QCPGraph>   m_graph;      // 需要绘制的曲线
};

class DataCollector : public QObject
{
    Q_OBJECT
public:
    explicit DataCollector(QObject *parent =0);

    void setChannel(int channel);
    void updateGraph(QPointer<QCPGraph>& graph);

public slots:
    void onDataComming(int channel, short data);

private:
    QVector<double>  m_xAxisValue;
    QVector<double>  m_dataContainer;
    QMutex           m_dataContainerMutex;
    int              m_channel;
};

#endif // PLOTAREA_H
