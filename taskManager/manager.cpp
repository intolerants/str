#include "manager.h"

Manager::Manager(QObject *parent):
    QThread(parent)
{

}

void Manager::run(){
    // Lista para receber as linhas do arquivo
    QStringList* stringList = new QStringList();

    //Arquivo para receber o stream out do comando
    QString fileName = "/home/tay/ufrn/intolerants/str/taskManager/out.txt";

    //Comando a ser executado
    QString command = "ps";

    //Executa o comando com o stream para o filename
    QProcess::execute(command + ">>" + fileName);

    //Leitura de linha a linha do arquivo
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            stringList->append(line);
        }
    inputFile.close();
    }

    emit sendList(stringList);
    //emit sendList(a);
}
