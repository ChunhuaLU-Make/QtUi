#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
#if 1
    QApplication a(argc, argv);
    MainWindow w;
    w.MyPrintf();
#endif
    qDebug() << "hello world";
    w.show();
    return a.exec();
}
