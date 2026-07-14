#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H

#include <QTimer>
#include <QWidget>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class TimerWindow;
}
QT_END_NAMESPACE

class TimerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TimerWindow(QWidget *parent = nullptr);

    ~TimerWindow();

    void setWorkMinutes(int min);
    void setRelaxMinutes(int min);
    void setCycleRounds(int count);
    void initDisplay();

signals:
    void timerStopped();

private slots:
    void on_stopBtn_clicked();
    void on_pauseBtn_clicked();
    void updateTime();

private:
    Ui::TimerWindow *ui;
    QSoundEffect  *m_soundPlayer;
    QTimer *m_timer;
    int m_remainingSec = 0;
    int m_workMinutes = 25;
    int m_relaxMinutes = 5;
    int m_cycleRounds = 4;
    int m_curRound = 1;
    bool m_isWorking = true;   // 工作状态标记
    bool m_started = false;    // 是否开始计时
    void updateTimeLabel();
    void finishTimer();
    void playSound(const QString &path);
};

#endif // TIMERWINDOW_H
