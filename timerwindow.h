#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H

#include <QTimer>
#include <QWidget>

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
    void updateDisplay();
    void initDisplay();
    void finishTimer();
signals:
    void timerStopped();

private slots:
    void on_stopBtn_clicked();
    void on_pauseBtn_clicked();

private:
    Ui::TimerWindow *ui;
    QTimer *m_timer;
    int m_remainingSec;
    int m_workMinutes;
    int m_relaxMinutes;
    int m_cycleRounds;
    int m_curRound = 1;
    bool m_isWorking = true;   // 工作状态标记
    void updateTime();
    void updateTimeLabel();
};

#endif // TIMERWINDOW_H
