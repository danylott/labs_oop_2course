#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMouseEvent>
#include <QDebug>
#include <QAction>
#include <QTimer>
#include <QMessageBox>
#include <QSound>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tmr = new QTimer();
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();

    initActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearCurrentTimer()
{
    ui->lstTimers->setCurrentRow(-1);
    ui->timeEdit->setTime(QTime::currentTime());
    ui->leName->clear();
    ui->rbTimer->setChecked(true);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int currentRow = ui->lstTimers->currentRow();
    qDebug()<< currentRow;
    if (currentRow != -1) {
        clearCurrentTimer();

    }

}

void MainWindow::on_btnAdd_clicked()
{
    qDebug()<<"Add clicked!";
    Timer* Timer = createTimer();

    Timers.push_back(Timer);

    ui->lstTimers->addItem(Timer->display());

}

void MainWindow::on_lstTimers_currentRowChanged(int currentRow)
{
    if (currentRow == -1) { // not selected
        qDebug()<<"No selected item";
        return;
    }
    Timer* Timer = Timers[currentRow];
    ui->leName->setText(Timer->getName().c_str());
    ui->timeEdit->setTime(Timer->getTime());
    ui->rbAlarm->setChecked(Timer->getType());
    ui->rbTimer->setChecked((Timer->getType() + 1) % 2);
}

void MainWindow::on_btnEdit_clicked()
{
    Timer* Timer = getCurrentTimer();
    if(!Timer)
        return;
    Timer = changeTimer(Timer);

    ui->lstTimers->currentItem()->setText(Timer->display());

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
    delete Timers[currentRow];
    Timers.erase(Timers.begin()+currentRow);
}

void MainWindow::updateTime()
{
    for(int i = 0; i < Timers.size(); i++) {
        Timer* Timer = Timers[i];
        if(Timer->getActive()) {
            if(Timer->changeRemainingTime()) {
               Timer->setActive(false);
               timerAlarm(Timer); // can restart timer
            }
        }
        ui->lstTimers->item(i)->setText(Timer->display());
    }
}


void MainWindow::initActions()
{
    QAction * deleteAction = new QAction("Delete",ui->lstTimers);

    connect(deleteAction,&QAction::triggered,this,&MainWindow::on_deleteAction_triggered);
    connect(ui->btnDelete,&QPushButton::clicked,deleteAction,&QAction::trigger);
    ui->lstTimers->addAction(deleteAction);
}

Timer* MainWindow::createTimer()
{
    Timer* Timer = new class Timer;
    Timer = changeTimer(Timer);
    return Timer;
}

Timer* MainWindow::changeTimer(Timer* Timer)
{
    string name = ui->leName->text().toUtf8().constData();
    Timer->setName(name);
    int type = ui->rbAlarm->isChecked(); // 1 if Alarm, 0 if Timer
    Timer->setType(type);
    QTime time = ui->timeEdit->time();
    Timer->setTime(time);

    Timer->setRemainingTime(Timer->calculateRemainingTime());
    return Timer;
}

Timer *MainWindow::getCurrentTimer()
{
    int currentRow = ui->lstTimers->currentRow();
    if (currentRow == -1) { return nullptr;}
    Timer* Timer = Timers[currentRow];
    return Timer;
}

void MainWindow::timerAlarm(Timer *Timer)
{
    auto player = new QMediaPlayer;

    player->setMedia(QUrl("http://download-sounds.ru/wp-content/uploads2/2012/05/23.mp3"));
    player->setVolume(50);
    player->play();
    QMessageBox msgBoxAlarm;
    msgBoxAlarm.setText(Timer->getName().c_str() + QString("ALARM!!!"));
    msgBoxAlarm.setIcon(QMessageBox::Critical);
    msgBoxAlarm.setInformativeText("What you want to do?");
    msgBoxAlarm.setStandardButtons(QMessageBox::Ok | QMessageBox::Retry | QMessageBox::Close);
    msgBoxAlarm.setDefaultButton(QMessageBox::Ok);
    int ret = msgBoxAlarm.exec();

    switch (ret) {
      case QMessageBox::Ok:
          break;
      case QMessageBox::Retry:
          Timer->setRemainingTime(Timer->calculateRemainingTime());
          Timer->setActive(true);
          player->stop();
          break;
      case QMessageBox::Close:
          player->stop();
          break;
      default:
          break;
    }
}


void MainWindow::on_btnStart_clicked()
{
    Timer* Timer = getCurrentTimer();
    if(!Timer)
        return;
    Timer->setActive(true);
    ui->lstTimers->currentItem()->setText(Timer->display());

}

void MainWindow::on_btnStop_clicked()
{
    Timer* Timer = getCurrentTimer();
    if(!Timer)
        return;
    Timer->setActive(false);

    ui->lstTimers->currentItem()->setText(Timer->display());
}
