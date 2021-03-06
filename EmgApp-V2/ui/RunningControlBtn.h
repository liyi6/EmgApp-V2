#ifndef RUNNINGCONTROLBTN_H
#define RUNNINGCONTROLBTN_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "CustomShadowEffect.h"

class RunningControlBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit RunningControlBtn(QWidget *parent = nullptr);
    ~RunningControlBtn();

    void setRunningStatus(bool running);

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool     m_running;
    QImage*  m_startImage;
    QImage*  m_stopImage;
};

#endif // RUNNINGCONTROLBTN_H
