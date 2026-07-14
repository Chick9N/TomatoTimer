#include "timerwindow.h"
#include "./ui_timerwindow.h"

#include <QDebug>
#include <QSoundEffect>


TimerWindow::TimerWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimerWindow)
    , m_timer(new QTimer(this))
{
    ui->setupUi(this);


    // 窗口置顶
    setWindowFlag(Qt::WindowStaysOnTopHint);

    ui->restartBtn->setEnabled(false);

    // 音效
    m_soundPlayer = new QSoundEffect(this);
    m_soundPlayer->setVolume(0.5);


    connect(m_timer,
            &QTimer::timeout,
            this,
            &TimerWindow::updateTime);
}


TimerWindow::~TimerWindow()
{
    delete ui;
}


// 设置工作时间
void TimerWindow::setWorkMinutes(int min)
{
    m_workMinutes = min;
}


// 设置休息时间
void TimerWindow::setRelaxMinutes(int min)
{
    m_relaxMinutes = min;
}


// 设置循环次数
void TimerWindow::setCycleRounds(int count)
{
    m_cycleRounds = count;
}


// 初始化显示
void TimerWindow::initDisplay()
{
    m_curRound = 1;

    m_isWorking = true;

    m_started = false;


    m_remainingSec =
        m_workMinutes * 60;


    ui->pauseBtn->setText("开始");


    ui->roundLabel->setText(
        QString("第 %1 / %2 轮")
            .arg(m_curRound)
            .arg(m_cycleRounds)
        );


    ui->stageLabel->setText(
        "准备开始工作"
        );


    updateTimeLabel();
}



// 开始/暂停/继续按钮
void TimerWindow::on_pauseBtn_clicked()
{

    // 第一次点击：开始
    if(!m_started)
    {

        m_started = true;


        m_timer->start(1000);


        ui->pauseBtn->setText("暂停");
        ui->stageLabel->setText("开始工作啦，加油努力吧！！");

        playSound("qrc:/work");


        qDebug()
            <<"开始计时";


        return;
    }



    // 已经开始

    if(m_timer->isActive())
    {

        // 暂停

        m_timer->stop();


        ui->pauseBtn->setText("继续");


        qDebug()
            <<"暂停";

    }
    else
    {

        // 继续

        m_timer->start(1000);


        ui->pauseBtn->setText("暂停");


        qDebug()
            <<"继续";

    }

}



// 停止
void TimerWindow::on_stopBtn_clicked()
{

    m_timer->stop();


    emit timerStopped();


    close();

}



// 每秒更新
void TimerWindow::updateTime()
{

    m_remainingSec--;


    updateTimeLabel();



    if(m_remainingSec <= 0)
    {

        if(m_isWorking)
        {

            // 工作结束

            playSound("qrc:/relax");


            m_isWorking = false;


            m_remainingSec =
                m_relaxMinutes * 60;


            ui->stageLabel->setText(
                "休息时间到，尽情享受吧~"
                );


        }
        else
        {

            // 休息结束

            m_curRound++;


            if(m_curRound > m_cycleRounds)
            {

                playSound("qrc:/finish");

                ui->restartBtn->setEnabled(false);

                finishTimer();


                return;

            }


            m_isWorking = true;


            playSound("qrc:/work");


            m_remainingSec =
                m_workMinutes * 60;


            ui->roundLabel->setText(
                QString("第 %1 / %2 轮")
                    .arg(m_curRound)
                    .arg(m_cycleRounds)
                );


            ui->stageLabel->setText(
                "开始工作啦，加油努力吧！！"
                );

        }


        updateTimeLabel();

    }

}



// 更新时间显示
void TimerWindow::updateTimeLabel()
{

    int minutes =
        m_remainingSec / 60;


    int seconds =
        m_remainingSec % 60;



    ui->timeLeftLabel->setText(
        QString("时间剩余: %1:%2")
            .arg(minutes,2,10,QChar('0'))
            .arg(seconds,2,10,QChar('0'))
        );

}



// 播放音效
void TimerWindow::playSound(const QString &path)
{

    qDebug()
    <<"播放"
    <<path;


    m_soundPlayer->setSource(
        QUrl(path)
        );


    m_soundPlayer->play();

}



// 完成
void TimerWindow::finishTimer()
{

    m_timer->stop();


    ui->stageLabel->setText(
        "番茄钟完成！"
        );


    ui->timeLeftLabel->setText(
        "时间剩余: 00:00"
        );


    ui->pauseBtn->setText(
        "完成"
        );


    ui->pauseBtn->setEnabled(false);

}

void TimerWindow::on_restartBtn_clicked()
{
    m_timer->stop();

    initDisplay();

    ui->pauseBtn->setEnabled(true);

    qDebug()<<"重新开始一组";
}

