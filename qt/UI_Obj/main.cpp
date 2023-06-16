#include <QApplication>
#include <QDebug>
#include <Python.h>
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

void MainCallPython(void)
{
    Py_Initialize();
    if ( !Py_IsInitialized() )
    {
        qDebug() << "Init fail";
        return;
    }
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.argv = ['python.py']");
    PyRun_SimpleString("sys.path.append('./')");

    //����scriptSecond.pyģ��
    PyObject* pModule = PyImport_ImportModule("WordToExcel");
    if (!pModule) {
        qDebug() << "Cant open python file!\n";
        return ;
    }

    //��ȡscriptSecondģ���е�temperImg����
    PyObject* pFunhello= PyObject_GetAttrString(pModule,"waht");

    if(!pFunhello){
        qDebug()<<"Get function hello failed";
        return ;
    }
    //����temperImg����
    PyObject_CallFunction(pFunhello,NULL);
    //�������ͷ�python
    Py_Finalize();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainCallPython();
    //MyTest test;
    //test.TestPirnt();
    MainWindow w;
    w.show();
    return a.exec();
}
