#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "ExcelOperation.h"

void ExcelTest(void)
{
    ExcelOperation fileExcel("E:\\Git\\QtUi\\TestDoc\\testEx.xlsx", "Sheet3");
    qDebug() << "workSheet:" << fileExcel.iWorkSheet;
    fileExcel.ExcelWriteExcel(1,1,"Waht you name");
    fileExcel.ExcelWriteExcel(1,2,"How are you");
    fileExcel.ExcelWriteExcel(1,3,"Yinli");

    fileExcel.ExcelUpdateRowColu();
    qDebug() << fileExcel.iRows << " " << fileExcel.iColumns;
    qDebug() << fileExcel.iStartRow << " " << fileExcel.iStartColumn;

    for(int i = fileExcel.iStartRow; i <= fileExcel.iRows+fileExcel.iStartRow - 1; i++)
    {
        for(int k = fileExcel.iStartColumn; k<=fileExcel.iColumns+fileExcel.iStartColumn-1; k++)
        {
            qDebug() << "i" << i << " k" << k;
            QString str = fileExcel.ExcelReadExcel(i,k);
            if(str.isEmpty() != true)
            qDebug() <<str;
        }
    }

}

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
