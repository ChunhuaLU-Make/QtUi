#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "ExcelOperation.h"

int main(int argc, char *argv[])
{
#if 1
    QApplication a(argc, argv);
    MainWindow w;
    //w.MyPrintf();
#endif
    QString strPath("E:\\Git\\QtUi\\TestDoc\\testEx.xlsx");
    ExcelOperation::ExcelReadExcel(strPath);
    qDebug() << "hello world";
    w.show();
    return a.exec();
}
