#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Task Manager");

    // Lista para receber as linhas do arquivo
    QStringList* stringList = new QStringList();

    // Modelo para receber a lista e ser setado na listView
    listModel = new QStringListModel(*stringList, NULL);

    ui->listView->setModel(listModel);
    manager = new Manager(this);
    connect(manager,SIGNAL(sendList(QStringList*)),this,SLOT(printList(QStringList*)));
    //connect(manager,SIGNAL(sendList(int)),this,SLOT(printList(int)));
    manager->start();

}

MainWindow::~MainWindow()
{
    manager->terminate();
    while(!manager->isFinished());
    delete ui;
}

void MainWindow::on_pushButton_kill_clicked()
{
    if (ui->lineEdit_PID->text() != "")
        kill(ui->lineEdit_PID->text().toInt(), SIGKILL);
    ui->lineEdit_PID->clear();
}

void MainWindow::on_pushButton_stop_clicked()
{
    if (ui->lineEdit_PID->text() != "")
        kill(ui->lineEdit_PID->text().toInt(), SIGSTOP);
    ui->lineEdit_PID->clear();
}

void MainWindow::on_pushButton_continue_clicked()
{
    if (ui->lineEdit_PID->text() != "")
        kill(ui->lineEdit_PID->text().toInt(), SIGCONT);
    ui->lineEdit_PID->clear();
}


void MainWindow::printList(QStringList *stringList)
{
    //listModel->sort(4, Qt::DescendingOrder);

    QMutableStringListIterator i(*stringList);
    while (i.hasNext()){
        QString next = i.next();
        if (!next.contains(filter)){
            if(!next.contains("PID"))
                i.remove();
        }
    }

    //Reseta o stringList atualizado
    listModel->setStringList(*stringList);

    ui->listView->setModel(listModel);

}

void MainWindow::on_lineEdit_filter_textChanged(const QString &arg1)
{
    filter.clear();
    filter.append(arg1);
}
