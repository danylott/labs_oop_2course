#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMouseEvent>
#include <QDebug>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearCurrentTimer()
{
    ui->lstTimers->setCurrentRow(-1);
    ui->timeEdit->clear();
    ui->leName->clear();
    ui->rbTimer->setChecked(true);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<event->isAccepted();
    int currentRow = ui->lstTimers->currentRow();
    qDebug()<< currentRow;
    if (currentRow != -1) {
        clearCurrentTimer();

    }

}

void MainWindow::on_btnAdd_clicked()
{
    qDebug()<<"Add clicked!";

    Timer Timer = createTimer();

    Timers.push_back(Timer);

    QString display_name = displayTimer(Timer);
    ui->lstTimers->addItem(display_name);

}

void MainWindow::on_lstTimers_currentRowChanged(int currentRow)
{
    if (currentRow == -1) { // not selected
        qDebug()<<"No selected item";
        return;
    }
    Timer Timer = Timers[currentRow];
    ui->leName->setText(Timer.getName().c_str());
    ui->timeEdit->setTime(Timer.getTime());
    ui->rbAlarm->setChecked(Timer.getType());
    ui->rbTimer->setChecked((Timer.getType() + 1) % 2);
}

void MainWindow::on_btnEdit_clicked()
{
    int currentRow = ui->lstTimers->currentRow();
    if (currentRow == -1) { return;}
    Timer& Timer = Timers[currentRow];

    Timer = createTimer();
    QString display_name = displayTimer(Timer);

    ui->lstTimers->currentItem()->setText(display_name);

}

void MainWindow::on_lstTimers_clicked(const QModelIndex &index)
{
}

void MainWindow::on_lstTimers_currentRowRemoved()
{
    qDebug()<<"Current Row Removed";
    clearCurrentTimer();
}

void MainWindow::on_deleteAction_triggered(bool checked)
{
    qDebug()<<"Delete triggered";
    int currentRow = ui->lstTimers->currentRow();
    if (currentRow == -1) {
        qDebug()<<"nothing to delete";
        return;
    }
    ui->lstTimers->takeItem(currentRow);
    clearCurrentTimer();
    Timers.erase(Timers.begin()+currentRow);
}


void MainWindow::initActions()
{
    QAction * deleteAction = new QAction("Delete",ui->lstTimers);

    connect(deleteAction,&QAction::triggered,this,&MainWindow::on_deleteAction_triggered);
    connect(ui->btnDelete,&QPushButton::clicked,deleteAction,&QAction::trigger);
    ui->lstTimers->addAction(deleteAction);
}

Timer MainWindow::createTimer()
{
    Timer Timer;
    string name = ui->leName->text().toUtf8().constData();
    Timer.setName(name);
    int type = ui->rbAlarm->isChecked(); // 1 if Alarm, 0 if Timer
    Timer.setType(type);
    QTime time = ui->timeEdit->time();
    Timer.setTime(time);
    return Timer;
}

QString MainWindow::displayTimer(Timer Timer)
{
    QString display_name = QString("%1: time: %2 %3").arg(Timer.getName().c_str()).arg(Timer.getTime().toString()).arg(Timer.getTypeString().c_str());
    return display_name;
}
