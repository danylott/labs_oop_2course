#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QListWidget>
#include <QTime>
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    ui->timer->setText(QTime::currentTime().toString());
}

void MainWindow::addTimerToList(int interval)
{
    QListWidgetItem * listItem = new QListWidgetItem(QIcon(":/res/images/timer.png"),QString(interval));
    listItem->setSizeHint( QSize(200, 400) );

    ui->listTimers->addItem(listItem);


}



void MainWindow::on_btnAddTimer_clicked()
{
    addTimerToList(10);
}
