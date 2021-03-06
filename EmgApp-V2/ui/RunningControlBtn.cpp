#include "RunningControlBtn.h"

RunningControlBtn::RunningControlBtn(QWidget *parent)
    : QPushButton(parent),
      m_running(false),
      m_startImage(nullptr),
      m_stopImage(nullptr)
{
    setMouseTracking(true);

    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(15.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(bodyShadow);

    m_stopImage = new QImage("res/stop.png");
    m_startImage = new QImage("res/start.png");
}

RunningControlBtn::~RunningControlBtn()
{
    if (m_stopImage) {
        delete m_stopImage;
        m_stopImage = nullptr;
    }

    if (m_startImage) {
        delete m_startImage;
        m_startImage = nullptr;
    }
}

void RunningControlBtn::setRunningStatus(bool running)
{
    m_running = running;
}

void RunningControlBtn::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (m_running) {
        painter.drawImage(this->rect(), *m_stopImage);
    } else {
        painter.drawImage(this->rect(), *m_startImage);
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
