#ifndef PLOTAREA_H
#define PLOTAREA_H

#include <QWidget>
#include "QCustomPlot.h"

class PlotArea : public QCustomPlot
{
    Q_OBJECT
public:
    explicit PlotArea(QWidget *parent = 0);

private:
    int     m_channel;    // 绘制通道

public slots:


};

#endif // PLOTAREA_H
