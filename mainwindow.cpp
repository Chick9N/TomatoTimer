#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "timerwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startBtn_clicked()
{
    TimerWindow *tw = new TimerWindow();    // 不能指定父窗口，否则内嵌显示。

    // 信号槽连接
    // 计时结束，显示主窗口
    connect(tw, &TimerWindow::timerStopped, this, &MainWindow::show);
    // 计时结束，释放资源
    tw->setAttribute(Qt::WA_DeleteOnClose);
    connect(tw, &TimerWindow::timerStopped, tw, &TimerWindow::close);

    // 新窗口设置状态
    tw->setWorkMinutes(ui->workTimeInput->value());
    tw->setRelaxMinutes(ui->relaxTimeInput->value());
    tw->setCycleRounds(ui->loopInput->value());

    tw->show();
    this->hide();
}


