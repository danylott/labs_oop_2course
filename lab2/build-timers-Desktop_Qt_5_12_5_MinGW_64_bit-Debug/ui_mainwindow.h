/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "customlistwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    CustomListWidget *lstTimers;
    QGroupBox *grbStudentDetails;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblName;
    QLineEdit *leName;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *lblTime;
    QTimeEdit *timeEdit;
    QPushButton *btnDelete;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblType;
    QRadioButton *rbTimer;
    QRadioButton *rbAlarm;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(831, 538);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lstTimers = new CustomListWidget(centralWidget);
        lstTimers->setObjectName(QString::fromUtf8("lstTimers"));
        lstTimers->setGeometry(QRect(10, 10, 421, 471));
        QFont font;
        font.setPointSize(12);
        lstTimers->setFont(font);
        lstTimers->setContextMenuPolicy(Qt::ActionsContextMenu);
        lstTimers->setSelectionMode(QAbstractItemView::NoSelection);
        grbStudentDetails = new QGroupBox(centralWidget);
        grbStudentDetails->setObjectName(QString::fromUtf8("grbStudentDetails"));
        grbStudentDetails->setGeometry(QRect(470, 20, 351, 431));
        layoutWidget = new QWidget(grbStudentDetails);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 221, 27));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lblName = new QLabel(layoutWidget);
        lblName->setObjectName(QString::fromUtf8("lblName"));

        horizontalLayout_2->addWidget(lblName);

        leName = new QLineEdit(layoutWidget);
        leName->setObjectName(QString::fromUtf8("leName"));

        horizontalLayout_2->addWidget(leName);

        btnAdd = new QPushButton(grbStudentDetails);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        btnAdd->setGeometry(QRect(10, 200, 93, 28));
        btnAdd->setCheckable(false);
        btnEdit = new QPushButton(grbStudentDetails);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));
        btnEdit->setGeometry(QRect(130, 200, 93, 28));
        layoutWidget1 = new QWidget(grbStudentDetails);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 70, 221, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lblTime = new QLabel(layoutWidget1);
        lblTime->setObjectName(QString::fromUtf8("lblTime"));

        horizontalLayout->addWidget(lblTime);

        timeEdit = new QTimeEdit(layoutWidget1);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 5)));
        timeEdit->setMinimumDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 5)));
        timeEdit->setMinimumTime(QTime(0, 0, 5));
        timeEdit->setTime(QTime(0, 0, 5));

        horizontalLayout->addWidget(timeEdit);

        btnDelete = new QPushButton(grbStudentDetails);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));
        btnDelete->setGeometry(QRect(250, 200, 88, 27));
        verticalLayoutWidget = new QWidget(grbStudentDetails);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 110, 221, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblType = new QLabel(verticalLayoutWidget);
        lblType->setObjectName(QString::fromUtf8("lblType"));

        verticalLayout->addWidget(lblType);

        rbTimer = new QRadioButton(verticalLayoutWidget);
        rbTimer->setObjectName(QString::fromUtf8("rbTimer"));

        verticalLayout->addWidget(rbTimer);

        rbAlarm = new QRadioButton(verticalLayoutWidget);
        rbAlarm->setObjectName(QString::fromUtf8("rbAlarm"));

        verticalLayout->addWidget(rbAlarm);

        btnStart = new QPushButton(grbStudentDetails);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(30, 250, 111, 41));
        btnStart->setCheckable(false);
        btnStop = new QPushButton(grbStudentDetails);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(200, 250, 111, 41));
        btnStop->setCheckable(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 831, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        grbStudentDetails->setTitle(QApplication::translate("MainWindow", "  Timer detail -- add / change timer", nullptr));
        lblName->setText(QApplication::translate("MainWindow", "Name:", nullptr));
        btnAdd->setText(QApplication::translate("MainWindow", "Add", nullptr));
        btnEdit->setText(QApplication::translate("MainWindow", "Edit", nullptr));
        lblTime->setText(QApplication::translate("MainWindow", "Time:", nullptr));
        timeEdit->setDisplayFormat(QApplication::translate("MainWindow", "H:mm:ss", nullptr));
        btnDelete->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        lblType->setText(QApplication::translate("MainWindow", "Type:", nullptr));
        rbTimer->setText(QApplication::translate("MainWindow", "Timer", nullptr));
        rbAlarm->setText(QApplication::translate("MainWindow", "Alarm", nullptr));
        btnStart->setText(QApplication::translate("MainWindow", "Start", nullptr));
        btnStop->setText(QApplication::translate("MainWindow", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
