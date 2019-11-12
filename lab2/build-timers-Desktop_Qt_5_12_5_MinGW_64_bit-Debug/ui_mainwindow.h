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
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *lblTime;
    QTimeEdit *timeEdit;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblType;
    QRadioButton *rbTimer;
    QRadioButton *rbAlarm;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblType_2;
    QRadioButton *rbRooster;
    QRadioButton *rbAhtung;
    QRadioButton *rbPipi;
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
        grbStudentDetails->setGeometry(QRect(440, 20, 351, 441));
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

        verticalLayoutWidget = new QWidget(grbStudentDetails);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 100, 221, 80));
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

        horizontalLayoutWidget = new QWidget(grbStudentDetails);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 360, 321, 71));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        btnStart = new QPushButton(horizontalLayoutWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setMinimumSize(QSize(40, 50));
        btnStart->setCheckable(false);

        horizontalLayout_3->addWidget(btnStart);

        btnStop = new QPushButton(horizontalLayoutWidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setMinimumSize(QSize(0, 50));
        btnStop->setCheckable(false);

        horizontalLayout_3->addWidget(btnStop);

        horizontalLayoutWidget_2 = new QWidget(grbStudentDetails);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 300, 321, 61));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        btnAdd = new QPushButton(horizontalLayoutWidget_2);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        btnAdd->setMinimumSize(QSize(0, 40));
        btnAdd->setCheckable(false);

        horizontalLayout_4->addWidget(btnAdd);

        btnEdit = new QPushButton(horizontalLayoutWidget_2);
        btnEdit->setObjectName(QString::fromUtf8("btnEdit"));
        btnEdit->setMinimumSize(QSize(0, 40));

        horizontalLayout_4->addWidget(btnEdit);

        btnDelete = new QPushButton(horizontalLayoutWidget_2);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));
        btnDelete->setMinimumSize(QSize(30, 40));

        horizontalLayout_4->addWidget(btnDelete);

        verticalLayoutWidget_2 = new QWidget(grbStudentDetails);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 190, 221, 105));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lblType_2 = new QLabel(verticalLayoutWidget_2);
        lblType_2->setObjectName(QString::fromUtf8("lblType_2"));

        verticalLayout_2->addWidget(lblType_2);

        rbRooster = new QRadioButton(verticalLayoutWidget_2);
        rbRooster->setObjectName(QString::fromUtf8("rbRooster"));

        verticalLayout_2->addWidget(rbRooster);

        rbAhtung = new QRadioButton(verticalLayoutWidget_2);
        rbAhtung->setObjectName(QString::fromUtf8("rbAhtung"));

        verticalLayout_2->addWidget(rbAhtung);

        rbPipi = new QRadioButton(verticalLayoutWidget_2);
        rbPipi->setObjectName(QString::fromUtf8("rbPipi"));

        verticalLayout_2->addWidget(rbPipi);

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
        lblTime->setText(QApplication::translate("MainWindow", "Time:", nullptr));
        timeEdit->setDisplayFormat(QApplication::translate("MainWindow", "H:mm:ss", nullptr));
        lblType->setText(QApplication::translate("MainWindow", "Type:", nullptr));
        rbTimer->setText(QApplication::translate("MainWindow", "Timer", nullptr));
        rbAlarm->setText(QApplication::translate("MainWindow", "Alarm", nullptr));
        btnStart->setText(QApplication::translate("MainWindow", "Start", nullptr));
        btnStop->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        btnAdd->setText(QApplication::translate("MainWindow", "Add", nullptr));
        btnEdit->setText(QApplication::translate("MainWindow", "Edit", nullptr));
        btnDelete->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        lblType_2->setText(QApplication::translate("MainWindow", "Music:", nullptr));
        rbRooster->setText(QApplication::translate("MainWindow", "Rooster", nullptr));
        rbAhtung->setText(QApplication::translate("MainWindow", "Ahtung", nullptr));
        rbPipi->setText(QApplication::translate("MainWindow", "Pi-pi-pi-pi", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
