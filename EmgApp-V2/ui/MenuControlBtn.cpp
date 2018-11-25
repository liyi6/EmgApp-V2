#include "MenuControlBtn.h"

MenuControlBtn::MenuControlBtn(QWidget *parent)
    : QPushButton(parent),
      m_backImage(nullptr)
{
    setMouseTracking(true);

    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(15.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(bodyShadow);

    m_backImage = new QImage("res/setting.png");
}

MenuControlBtn::~MenuControlBtn()
{
    if (m_backImage) {
        delete m_backImage;
        m_backImage = nullptr;
    }
}

void MenuControlBtn::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(this->rect(), *m_backImage);
}

void MenuControlBtn::enterEvent(QEvent *)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(25.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 150));
    setGraphicsEffect(bodyShadow);
}

void MenuControlBtn::leaveEvent(QEvent *)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(15.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(bodyShadow);
}

void MenuControlBtn::mousePressEvent(QMouseEvent *event)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(30.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 200));
    setGraphicsEffect(bodyShadow);

    QPushButton::mousePressEvent(event);
}

void MenuControlBtn::mouseReleaseEvent(QMouseEvent *event)
{
    CustomShadowEffect *bodyShadow = new CustomShadowEffect();
    bodyShadow->setBlurRadius(25.0);
    bodyShadow->setDistance(6.0);
    bodyShadow->setColor(QColor(0, 0, 0, 150));
    setGraphicsEffect(bodyShadow);

    QPushButton::mouseReleaseEvent(event);
}
