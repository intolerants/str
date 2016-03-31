#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Task Manager");
    manager = new Manager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_kill_clicked()
{
    kill(ui->lineEdit_PID->text().toInt(), SIGKILL);
    ui->lineEdit_PID->clear();
}

void MainWindow::on_pushButton_stop_clicked()
{
    kill(ui->lineEdit_PID->text().toInt(), SIGSTOP);
    ui->lineEdit_PID->clear();
}

void MainWindow::on_pushButton_continue_clicked()
{
    kill(ui->lineEdit_PID->text().toInt(), SIGCONT);
    ui->lineEdit_PID->clear();
}



//// Lista para receber as linhas do arquivo
//QStringList* stringList = new QStringList();
//// Modelo para receber a lista e ser setado na listView
//QStringListModel* listModel = new QStringListModel(*stringList, NULL);
//ui->listView->setModel(listModel);

////Arquivo para receber o stream out do comando
//QString fileName = "out.txt";
////Comando a ser executado
//QString command = "ps";
////Executa o comando com o stream para o filename
//QProcess::execute (command + ">>" + fileName);
////Leitura de linha a linha do arquivo
//QFile inputFile(fileName);
//if (inputFile.open(QIODevice::ReadOnly))
//{
//QTextStream in(&inputFile);
//while (!in.atEnd())
//{
//QString line = in.readLine();
//stringList->append(line);
//}
//inputFile.close();
//}
////Reseta o stringList atualizado
//listModel->setStringList(*stringList);
//}
