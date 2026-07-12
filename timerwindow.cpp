#include "timerwindow.h"
#include "./ui_timerwindow.h"
#include "QDebug"

TimerWindow::TimerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimerWindow)
    , m_timer(new QTimer(this))
{
    ui->setupUi(this);
    connect(m_timer,
            &QTimer::timeout,
            this,
            &TimerWindow::updateTime);
}

TimerWindow::~TimerWindow()
{
    delete ui;
}

void TimerWindow::setWorkMinutes(int min)
{
    this->m_workMinutes = min;
    initDisplay();
    qDebug() << "工作时长设置为：" << min;
}

void TimerWindow::setRelaxMinutes(int min)
{
    this->m_relaxMinutes = min;
    initDisplay();
    qDebug() << "休息时长设置为：" << min;
}

void TimerWindow::setCycleRounds(int count)
{
    this->m_cycleRounds = count;
    initDisplay();
    qDebug() << "循环轮数设置为：" << count;
}

void TimerWindow::initDisplay(){
    ui->roundLabel->setText(
        QString("第 %1 / %2 轮")
            .arg(m_curRound)
            .arg(m_cycleRounds)
        );

    ui->timeLeftLabel->setText(
        QString("时间剩余:  %1:%2")
            .arg(m_workMinutes,2,10,QChar('0'))
            .arg(0,2,10,QChar('0')));

    ui->stageLabel->setText("开始工作啦，加油努力吧！！");

    m_remainingSec = m_workMinutes * 60;
}

void TimerWindow::on_stopBtn_clicked()
{
    close();
    emit timerStopped();
}


void TimerWindow::on_pauseBtn_clicked()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
        qDebug()<<"倒计时停止";
        ui->pauseBtn->setText("继续");
    }
    else
    {
        m_timer->start(1000);
        qDebug()<<"倒计时开始";
        ui->pauseBtn->setText("暂停");
    }
}

void TimerWindow::updateTime()
{
    m_remainingSec--;

    updateTimeLabel();


    if(m_remainingSec <= 0)
    {
        if(m_isWorking)
        {
            // 工作结束

            m_isWorking = false;

            m_remainingSec = m_relaxMinutes * 60;

            ui->stageLabel->setText(
                "休息时间到，尽情享受吧~"
                );
        }
        else
        {
            // 休息结束

            m_isWorking = true;

            m_curRound++;

            if(m_curRound > m_cycleRounds)
            {
                finishTimer();
                return;
            }

            m_remainingSec = m_workMinutes * 60;

            ui->stageLabel->setText(
                "开始工作啦，加油努力吧！！"
                );
        }

        updateTimeLabel();
    }
}

void TimerWindow::updateTimeLabel()
{
    int minutes = m_remainingSec / 60;
    int seconds = m_remainingSec % 60;

    ui->timeLeftLabel->setText(
        QString("时间剩余: %1:%2")
            .arg(minutes,2,10,QChar('0'))
            .arg(seconds,2,10,QChar('0'))
        );
}

void TimerWindow::finishTimer()
{
    // 停止计时器
    m_timer->stop();

    // 设置状态
    ui->stageLabel->setText("番茄钟完成！");

    // 时间归零
    m_remainingSec = 0;

    ui->timeLeftLabel->setText("时间剩余: 00:00");

    // 禁用暂停按钮
    ui->pauseBtn->setEnabled(false);
}
