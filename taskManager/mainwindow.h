#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStringListModel>
#include <QFile>
#include <QProcess>
#include <manager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QStringListModel* listModel;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Manager *manager;
    QString filter;

private slots:
    void on_pushButton_kill_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_continue_clicked();

    void on_pushButton_filter_clicked();

    void on_lineEdit_filter_textChanged(const QString &arg1);

public slots:
     void printList(QStringList *stringList);
    //void printList(int);

};

#endif // MAINWINDOW_H
