#ifndef FULLSCREENCONTROLBTN_H
#define FULLSCREENCONTROLBTN_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "CustomShadowEffect.h"

class FullscreenControlBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit FullscreenControlBtn(QWidget *parent = nullptr);
    ~FullscreenControlBtn();

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QImage*  m_fullImage;
    QImage*  m_normalImage;
};
#endif // FULLSCREENCONTROLBTN_H
