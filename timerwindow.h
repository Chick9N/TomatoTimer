#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H

#include <QObject>

class timerwindow : public QObject
{
    Q_OBJECT
public:
    explicit timerwindow(QObject *parent = nullptr);

signals:
};

#endif // TIMERWINDOW_H
