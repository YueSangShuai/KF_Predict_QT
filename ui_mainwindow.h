/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QCustomPlot *widget_1;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1319, 797);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_1 = new QCustomPlot(centralwidget);
        widget_1->setObjectName(QString::fromUtf8("widget_1"));

        horizontalLayout->addWidget(widget_1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(70, 2000));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBox_1 = new QCheckBox(widget);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setEnabled(true);
        checkBox_1->setChecked(true);

        verticalLayout->addWidget(checkBox_1);

        checkBox_2 = new QCheckBox(widget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setChecked(true);

        verticalLayout->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(widget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        verticalLayout->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(widget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        verticalLayout->addWidget(checkBox_4);


        horizontalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1319, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        checkBox_1->setText(QCoreApplication::translate("MainWindow", "\346\263\242\345\275\2421", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "\346\263\242\345\275\2422", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "\346\263\242\345\275\2423", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "\346\263\242\345\275\2424", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
