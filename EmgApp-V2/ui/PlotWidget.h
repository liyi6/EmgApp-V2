#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include "QCustomPlot.h"
#include "EmgDataReceiver.h"
#include "AppContext.h"

class PlotWidget : public QCustomPlot
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = nullptr);

    void start();
    void stop();
    void setChannel(int channel);

private slots:
    void onReplot();

private:
    QTimer*              m_plotTimer;  // 刷新定时器
    int                  m_channel;    // 绘制通道
    QPointer<QCPGraph>   m_graph;      // 需要绘制的曲线
};

#endif // PLOTWIDGET_H
