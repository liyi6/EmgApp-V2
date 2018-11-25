#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_curPage(0),
    m_runStatus(NotRunning)
{
    ui->setupUi(this);
    updateUi();

    connect(this, SIGNAL(start()), EmgDataRecorder::instance(), SLOT(onStartRecord()), Qt::QueuedConnection);
    connect(this, SIGNAL(start()), EmgDataReceiver::instance(), SLOT(onSendStartCmd()), Qt::QueuedConnection);

    connect(this, SIGNAL(stop()), EmgDataRecorder::instance(), SLOT(onStopRecord()), Qt::QueuedConnection);
    connect(this, SIGNAL(stop()), EmgDataReceiver::instance(), SLOT(onSendStopCmd()), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *)
{
    if (Qt::WindowFullScreen == windowState() && !ui->ctrlPanel->isVisible()) {
        ui->ctrlPanel->setVisible(true);
    }
}

void MainWindow::updateUi()
{
    setWindowIcon(QIcon("res/logo.ico"));
    setWindowTitle("EMG Demo");

//    CustomShadowEffect *ctrlPanelShadow = new CustomShadowEffect();
//    ctrlPanelShadow->setBlurRadius(20.0);
//    ctrlPanelShadow->setDistance(6.0);
//    ctrlPanelShadow->setColor(QColor(0, 0, 0, 80));
//    ui->ctrlPanel->setGraphicsEffect(ctrlPanelShadow);

    CustomShadowEffect *dataPanelShadow = new CustomShadowEffect();
    dataPanelShadow->setBlurRadius(20.0);
    dataPanelShadow->setDistance(6.0);
    dataPanelShadow->setColor(QColor(0, 0, 0, 80));
    ui->dataPanel->setGraphicsEffect(dataPanelShadow);

    for (int channel=0; channel<CHANNEL_SIZE; channel++) {
        // set plot channel
        QString plotControlName = "channel" + QString::number(channel);
        PlotWidget* plot = this->findChild<PlotWidget*>(plotControlName);
        if (!plot) {
            qWarning() << "Find plot error: can't find~~~ " << plotControlName;
            continue;
        }
        plot->setChannel(channel);
    }

    ui->stackedWidget->setCurrentIndex(m_curPage);
}

void MainWindow::on_btnFsc_clicked()
{
    if (Qt::WindowFullScreen == windowState()) {

        showNormal();
        ui->ctrlPanel->setVisible(true);

    } else {

        QPropertyAnimation *pScaleAnimation1 = new QPropertyAnimation(ui->ctrlPanel, "geometry");
        pScaleAnimation1->setDuration(500);
        pScaleAnimation1->setStartValue(ui->ctrlPanel->geometry());
        pScaleAnimation1->setEndValue(QRect(ui->ctrlPanel->x(), ui->ctrlPanel->y()+ui->ctrlPanel->height(), ui->ctrlPanel->width(), 0));
        pScaleAnimation1->setEasingCurve(QEasingCurve::InOutQuad);

        connect(pScaleAnimation1, SIGNAL(finished()), this, SLOT(onHideCtrl()));

        QPropertyAnimation *pScaleAnimation2 = new QPropertyAnimation(ui->dataPanel, "geometry");
        pScaleAnimation2->setDuration(500);
        pScaleAnimation2->setStartValue(ui->dataPanel->geometry());
        pScaleAnimation2->setEndValue(ui->centralwidget->geometry());
        pScaleAnimation2->setEasingCurve(QEasingCurve::InOutQuad);

        QParallelAnimationGroup* group = new QParallelAnimationGroup(this);
        group->addAnimation(pScaleAnimation1);
        group->addAnimation(pScaleAnimation2);


        QPropertyAnimation *pScaleAnimation3 = new QPropertyAnimation(this, "geometry");
        pScaleAnimation3->setDuration(500);
        pScaleAnimation3->setStartValue(geometry());
        pScaleAnimation3->setEndValue(QApplication::desktop()->screenGeometry());
        pScaleAnimation3->setEasingCurve(QEasingCurve::InOutQuad);

        QSequentialAnimationGroup *pPosGroup = new QSequentialAnimationGroup(this);
        pPosGroup->addPause(500);
        pPosGroup->addAnimation(group);
        pPosGroup->addAnimation(pScaleAnimation3);

        pPosGroup->start(QAbstractAnimation::DeleteWhenStopped);

        //showFullScreen();
    }
}

void MainWindow::on_btnStart_clicked()
{
    if (NotRunning == m_runStatus) {
        connect(EmgDataReceiver::instance(), SIGNAL(orignalDataComming(QByteArray)), EmgDataRecorder::instance(), SLOT(onOrignalDataComming(QByteArray)), Qt::QueuedConnection);
        emit start();

        for (int channel=m_curPage*4; channel<m_curPage*4+4; channel++) {
            qDebug() << channel;
            QString plotControlName = "channel" + QString::number(channel);
            PlotWidget* plot = this->findChild<PlotWidget*>(plotControlName);
            if (!plot) {
                qWarning() << "Find plot error: can't find~~~ " << plotControlName;
            } else {
                plot->start();
            }
        }

        m_runStatus = Running;
    } else {
        disconnect(EmgDataReceiver::instance(), SIGNAL(orignalDataComming(QByteArray)), EmgDataRecorder::instance(), SLOT(onOrignalDataComming(QByteArray)));
        emit stop();

        for (int channel=m_curPage*4; channel<m_curPage*4+4; channel++) {
            QString plotControlName = "channel" + QString::number(channel);
            PlotWidget* plot = this->findChild<PlotWidget*>(plotControlName);
            if (!plot) {
                qWarning() << "Find plot error: can't find~~~ " << plotControlName;
            } else {
                plot->stop();
            }
        }

        m_runStatus = NotRunning;
    }
}

void MainWindow::on_btnPrePage_clicked()
{
    if (m_curPage <=0) {
        qWarning() << "Already first page, no more pre page.";
        return;
    }

    // 先停止当前界面的刷新
    for (int channel=m_curPage*4; channel<m_curPage*4+4; channel++) {
        QString plotControlName = "channel" + QString::number(channel);
        PlotWidget* plot = this->findChild<PlotWidget*>(plotControlName);
        if (!plot) {
            qWarning() << "Find plot error: can't find~~~ " << plotControlName;
        } else {
            plot->stop();
        }
    }
    // 开启pre页面的栓新
    m_curPage--;
    for (int channel=m_curPage*4; channel<m_curPage*4+4; channel++) {
        QString plotControlName = "channel" + QString::number(channel);
        PlotWidget* plot = this->findChild<PlotWidget*>(plotControlName);
        if (!plot) {
            qWarning() << "Find plot error: can't find~~~ " << plotControlName;
        } else {
            plot->start();
        }
    }

    ui->stackedWidget->setCurrentIndex(m_curPage);
}

void MainWindow::on_btnNextPage_clicked()
{
    if (m_curPage >=PAGE_COUNT-1) {
        qWarning() << "Already last page, no more next page.";
        return;
    }

    // 先停止当前界面的刷新
    for (int channel=m_curPage*4; channel<m_curPage*4+4; channel++) {
        QString plotControlName = "channel" + QString::number(channel);
        PlotWidget* plot = this->findChild<PlotWidget*>(plotControlName);
        if (!plot) {
            qWarning() << "Find plot error: can't find~~~ " << plotControlName;
        } else {
            plot->stop();
        }
    }
    // 开启pre页面的栓新
    m_curPage++;
    for (int channel=m_curPage*4; channel<m_curPage*4+4; channel++) {
        QString plotControlName = "channel" + QString::number(channel);
        PlotWidget* plot = this->findChild<PlotWidget*>(plotControlName);
        if (!plot) {
            qWarning() << "Find plot error: can't find~~~ " << plotControlName;
        } else {
            plot->start();
        }
    }

    ui->stackedWidget->setCurrentIndex(m_curPage);
}

void MainWindow::onHideCtrl()
{
    ui->ctrlPanel->setVisible(false);
}
