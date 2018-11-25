#include "FullscreenControlBtn.h"

FullscreenControlBtn::FullscreenControlBtn(QWidget *parent)
    : QPushButton(parent),
      m_fullImage(nullptr),
      m_normalImage(nullptr)
{
    setMouseTracking(true);

    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(15.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(bodyShadow);

    m_fullImage = new QImage("res/fsc.png");
    m_normalImage = new QImage("res/fsc.png");
}

FullscreenControlBtn::~FullscreenControlBtn()
{
    if (m_fullImage) {
        delete m_fullImage;
        m_fullImage = nullptr;
    }

    if (m_normalImage) {
        delete m_normalImage;
        m_normalImage = nullptr;
    }
}

void FullscreenControlBtn::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (Qt::WindowFullScreen == windowState()) {
        painter.drawImage(this->rect(), *m_fullImage);
    } else {
        painter.drawImage(this->rect(), *m_normalImage);
    }
}

void FullscreenControlBtn::enterEvent(QEvent *)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(25.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 150));
    setGraphicsEffect(bodyShadow);
}

void FullscreenControlBtn::leaveEvent(QEvent *)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(15.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(bodyShadow);
}

void FullscreenControlBtn::mousePressEvent(QMouseEvent *event)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(30.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 200));
    setGraphicsEffect(bodyShadow);

    QPushButton::mousePressEvent(event);
}

void FullscreenControlBtn::mouseReleaseEvent(QMouseEvent *event)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(25.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 150));
    setGraphicsEffect(bodyShadow);

    QPushButton::mouseReleaseEvent(event);
}
