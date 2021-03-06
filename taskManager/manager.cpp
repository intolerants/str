#include "manager.h"

Manager::Manager(QObject *parent):
    QThread(parent)
{

}

void Manager::run(){
    double time = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    while(1){
        if (QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0 - time >= 2){
            time = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

            // Lista para receber as linhas do arquivo
            QStringList* stringList = new QStringList();

            //Arquivo para receber o stream out do comando
            QString fileName = "out.txt";

            //Comando a ser executado
            QString command = "/bin/sh -c \"ps -auxf\"";

            //Executa o comando com o stream para o filename
            system("> out.txt");
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
    }
}
