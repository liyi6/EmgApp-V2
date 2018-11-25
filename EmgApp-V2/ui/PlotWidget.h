#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>
#include <QEvent>
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

signals:
    void leftSlide();
    void rightSlide();

protected:
    virtual void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private slots:
    void onReplot();

private:
    void updateUi();

private:
    QTimer*              m_plotTimer;       // 刷新定时器
    int                  m_channel;         // 绘制通道
    QPointer<QCPGraph>   m_graph;           // 需要绘制的曲线
    bool                 m_isMousePressed;  // 鼠标是否按下(windows平板手指是否按下)
    QPoint               m_startPoint;      // 鼠标按下时的位置
};

#endif // PLOTWIDGET_H
