/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QListView *listView;
    QWidget *tab_2;
    QGroupBox *groupBox_flitro;
    QLineEdit *lineEdit_filter;
    QGroupBox *groupBox;
    QLineEdit *lineEdit_PID;
    QPushButton *pushButton_kill;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_continue;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(599, 675);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 601, 451));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(20, 20, 552, 381));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 550, 379));
        listView = new QListView(scrollAreaWidgetContents);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(0, 0, 551, 381));
        scrollArea->setWidget(scrollAreaWidgetContents);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        groupBox_flitro = new QGroupBox(centralWidget);
        groupBox_flitro->setObjectName(QStringLiteral("groupBox_flitro"));
        groupBox_flitro->setGeometry(QRect(20, 460, 511, 71));
        lineEdit_filter = new QLineEdit(groupBox_flitro);
        lineEdit_filter->setObjectName(QStringLiteral("lineEdit_filter"));
        lineEdit_filter->setGeometry(QRect(20, 30, 291, 27));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 530, 511, 91));
        lineEdit_PID = new QLineEdit(groupBox);
        lineEdit_PID->setObjectName(QStringLiteral("lineEdit_PID"));
        lineEdit_PID->setGeometry(QRect(20, 50, 113, 27));
        pushButton_kill = new QPushButton(groupBox);
        pushButton_kill->setObjectName(QStringLiteral("pushButton_kill"));
        pushButton_kill->setGeometry(QRect(160, 50, 99, 27));
        pushButton_stop = new QPushButton(groupBox);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        pushButton_stop->setGeometry(QRect(270, 50, 99, 27));
        pushButton_continue = new QPushButton(groupBox);
        pushButton_continue->setObjectName(QStringLiteral("pushButton_continue"));
        pushButton_continue->setGeometry(QRect(380, 50, 99, 27));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 67, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 599, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Lista", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Gr\303\241ficos", 0));
        groupBox_flitro->setTitle(QApplication::translate("MainWindow", "Filter", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Actions", 0));
        lineEdit_PID->setText(QString());
        pushButton_kill->setText(QApplication::translate("MainWindow", "Kill", 0));
        pushButton_stop->setText(QApplication::translate("MainWindow", "Stop", 0));
        pushButton_continue->setText(QApplication::translate("MainWindow", "Continue", 0));
        label->setText(QApplication::translate("MainWindow", "PID", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
