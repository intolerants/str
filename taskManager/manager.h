#ifndef MANAGER_H
#define MANAGER_H

#include <signal.h>
#include <QThread>
#include <QProcess>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDebug>

class Manager : public QThread
{
    Q_OBJECT

public:
    explicit Manager(QObject *parent = 0);
    void run();

private:
    typedef QThread super;

signals:
    void sendList(QStringList*);
    //void sendList(int a);
};

#endif // MANAGER_H
