#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addTimerToList(int interval);
private slots:
    void updateTime();

    void on_btnAddTimer_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
};
#endif // MAINWINDOW_H
