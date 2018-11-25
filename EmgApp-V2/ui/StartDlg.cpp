#include "StartDlg.h"
#include "ui_StartDlg.h"

StartDlg::StartDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDlg)
{
    ui->setupUi(this);
    updateUi();
}

StartDlg::~StartDlg()
{
    delete ui;
}

void StartDlg::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(this->rect(),QImage("res/cover.jpg"));
}

void StartDlg::updateUi()
{
    setWindowIcon(QIcon("res/logo.ico"));
    setWindowTitle("EMG Demo");
    setFixedSize(640, 360);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    ui->btnConnect->setStyleSheet("background-color: qradialgradient(spread:reflect, cx:0.5, cy:0.5, radius:0.5, fx:0.494, fy:0.506, stop:0.0852273 rgba(255, 255, 255, 255), stop:0.892045 rgba(0, 0, 0, 227));color: rgb(0, 0, 0);");

    connect(ui->btnConnect, SIGNAL(clicked(bool)), EmgDataReceiver::instance(), SLOT(onConnectToHost()));
    connect(EmgDataReceiver::instance(), SIGNAL(netConnected()), this, SLOT(onConnected()), Qt::QueuedConnection);
    connect(EmgDataReceiver::instance(), SIGNAL(netError()), this, SLOT(onConnectError()), Qt::QueuedConnection);
}

void StartDlg::onConnected()
{
    qDebug() << "Connect to host success.";
    accept();
    disconnect(EmgDataReceiver::instance(), SIGNAL(netConnected()), this, SLOT(onConnected()));
    disconnect(EmgDataReceiver::instance(), SIGNAL(netError()), this, SLOT(onConnectError()));
}

void StartDlg::onConnectError()
{
    qWarning() << "Connect to host failed.";
    QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("连接服务器失败,请检查网络或者是服务是否开启"), QMessageBox::Ok);
}
