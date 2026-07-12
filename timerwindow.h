#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H

#include "mainwindow.h"
#include <QWidget>

class TimerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TimerWindow(QWidget *parent = nullptr);

signals:

private:
    Ui::MainWindow *ui;

    int m_workMinutes;
    int m_relaxMinutes;
    int m_cycleRounds;
};

#endif // TIMERWINDOW_H
