#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //CallPyInterface callFunc;
    //callFunc.CallNotParameter();
    //callFunc.CallParameter(2,4);
    w.show();
    return a.exec();
}
