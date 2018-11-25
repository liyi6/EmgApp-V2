#ifndef SETTINGDLG_H
#define SETTINGDLG_H

#include <QDialog>
#include "CustomShadowEffect.h"

namespace Ui {
class SettingDlg;
}

class SettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDlg(QWidget *parent = nullptr);
    ~SettingDlg();

private:
    void updateUi();

private:
    Ui::SettingDlg *ui;
};

#endif // SETTINGDLG_H
