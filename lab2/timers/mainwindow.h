#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "timer.h"

#include <QMainWindow>

#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void on_btnAdd_clicked();

    void on_lstTimers_currentRowChanged(int currentRow);

    void on_btnEdit_clicked();

    void on_lstTimers_clicked(const QModelIndex &index);

    void on_lstTimers_currentRowRemoved();
    void on_deleteAction_triggered(bool checked);

    void updateTime();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *tmr;

    std::vector<Timer*> Timers;
    void initActions();
    Timer* createTimer();
    Timer* changeTimer(Timer* Timer);
    Timer* getCurrentTimer();
    void timerAlarm(Timer* Timer);

    void clearCurrentTimer();
};

#endif // MAINWINDOW_H
