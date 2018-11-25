#ifndef MENUCONTROLBTN_H
#define MENUCONTROLBTN_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include "CustomShadowEffect.h"

class MenuControlBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit MenuControlBtn(QWidget *parent = nullptr);
    ~MenuControlBtn();

protected:
    virtual void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    virtual void enterEvent(QEvent* event) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent* event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QImage*  m_backImage;
};

#endif // MENUCONTROLBTN_H
