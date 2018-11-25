#include "RunningControlBtn.h"

RunningControlBtn::RunningControlBtn(QWidget *parent)
    : QPushButton(parent),
      m_running(false)
{
    setMouseTracking(true);

    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(15.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(bodyShadow);
}

void RunningControlBtn::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (m_running) {
        painter.drawImage(this->rect(),QImage("res/stop.png"));
    } else {
        painter.drawImage(this->rect(),QImage("res/start.png"));
    }
}

void RunningControlBtn::enterEvent(QEvent *)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(25.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 150));
    setGraphicsEffect(bodyShadow);
}

void RunningControlBtn::leaveEvent(QEvent *)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(15.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(bodyShadow);
}

void RunningControlBtn::mousePressEvent(QMouseEvent *event)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(30.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 200));
    setGraphicsEffect(bodyShadow);

    QPushButton::mousePressEvent(event);
}

void RunningControlBtn::mouseReleaseEvent(QMouseEvent *event)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(25.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 150));
    setGraphicsEffect(bodyShadow);

    QPushButton::mouseReleaseEvent(event);
}

bool RunningControlBtn::event(QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress) {
        m_running = !m_running;
    }
    return QPushButton::event(e);
}
