#include "mainwindow.h"

#include <QApplication>
#include "rep_remoteObject_replica.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
