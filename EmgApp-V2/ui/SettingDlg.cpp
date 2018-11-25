#include "SettingDlg.h"
#include "ui_SettingDlg.h"

SettingDlg::SettingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDlg)
{
    ui->setupUi(this);
    updateUi();
}

SettingDlg::~SettingDlg()
{
    delete ui;
}

void SettingDlg::updateUi()
{
    setWindowFlags(Qt::FramelessWindowHint);      // 无边框
    //setAttribute(Qt::WA_TranslucentBackground);   // 背景透明

//    CustomShadowEffect *shadowEffect = new CustomShadowEffect();
//    shadowEffect->setBlurRadius(20.0);
//    shadowEffect->setDistance(6.0);
//    shadowEffect->setColor(QColor(0, 0, 0, 80));
//    setGraphicsEffect(shadowEffect);
}
