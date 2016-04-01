#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Task Manager");

    ////////////////Inicio Thread////////////////////
    // Lista para receber as linhas do arquivo
    QStringList* stringList = new QStringList();

    // Modelo para receber a lista e ser setado na listView
    QStringListModel* listModel = new QStringListModel(*stringList, NULL);

    ui->listView->setModel(listModel);
    manager = new Manager(this);
    connect(manager,SIGNAL(sendList(QStringList*)),this,SLOT(printList(QStringList*)));
    //connect(manager,SIGNAL(sendList(int)),this,SLOT(printList(int)));
    manager->start();
    //////////////////Fim Thread/////////////////////
}

MainWindow::~MainWindow()
{
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

//void MainWindow::printList(int a)
//{
//    qDebug() << a;
//    ui->pushButton_continue->setDisabled(true);
//}

void MainWindow::printList(QStringList *stringList)
{
    qDebug() << "a";
    // Modelo para receber a lista e ser setado na listView
    QStringListModel* listModel = new QStringListModel();

    //Reseta o stringList atualizado
    listModel->setStringList(*stringList);
    ui->listView->setModel(listModel);
}


