#include "mainwindow.h"

#include <QApplication>
#include <QDebug>


class Father
{
public:
    Father()
    {
        qDebug() << "This is father gouzhao";
    }
    ~Father()
    {
        qDebug() << "This is father xigou";
    }
};

void MyTest()
{
    Father* father = NULL;
    qDebug() << "Start";
    father = new Father;
    qDebug() << "Start gouzhao";
    if(father != NULL)
    delete father;
}

int main(int argc, char *argv[])
{
#if 1
    QApplication a(argc, argv);
    MainWindow w;
    //w.MyPrintf();
    //MyTest();
#endif
    //ExcelTest();

    qDebug() << "hello world";
    w.show();
    return a.exec();
}
