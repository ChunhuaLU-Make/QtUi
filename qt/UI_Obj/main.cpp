#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

class MyTest
{
public:
    MyTest()
    {
        qDebug() << "This is GouZhao";
    }
    int *a = NULL;

    ~MyTest()
    {
        delete a;
        qDebug() << "This is XiGou";
    }

    void TestPirnt()
    {
        qDebug()<<"Hello world";
    }
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MyTest test;
    //test.TestPirnt();
    MainWindow w;
    w.show();
    return a.exec();
}
