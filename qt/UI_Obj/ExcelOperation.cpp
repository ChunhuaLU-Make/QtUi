#include "ExcelOperation.h"


#include <QFile>
#include <QDir>
#include <QObject>
#include <QString>
#include <QDebug>

#if defined(Q_OS_WIN)

#include <windows.h>
#endif // Q_OS_WIN
#include <QVariant>


ExcelOperation::ExcelOperation(QString path, QString sheetName)
{
    /* Open excel file.*/

    if(false == ExcelOperation::ExcelCheckFile(path))
    {
        qDebug() << "Open file error";
        return;
    }

    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    excel = new QAxObject("Excel.Application");
    excel->dynamicCall("SetVisible(bool)", false);
    workbooks = excel->querySubObject("WorkBooks");


    // Open path file.
    workbook = workbooks->querySubObject("Open(QString&)", path);

    // Get opened excel file all work sheet.
    worksheets = workbook->querySubObject("WorkSheets");

    iWorkSheet = worksheets->property("Count").toInt();

    this->worksheet = ExcelOpenWorkSheet(sheetName);
    if(this->worksheet == NULL)
    {
        qDebug() << "Not SheetName:" << sheetName;
        return ;
    }

    //—————————获取该sheet的数据范围（可以理解为有数据的矩形区域）————
    QAxObject* usedrange = worksheet->querySubObject("UsedRange");

    //———————————————————获取行数———————————————
    QAxObject* rows = usedrange->querySubObject("Rows");
    iRows = rows->property("Count").toInt();

    //————————————获取列数—————————
    QAxObject* columns = usedrange->querySubObject("Columns");
    iColumns = columns->property("Count").toInt();

    //————————数据的起始行———
    iStartRow = rows->property("Row").toInt();

    //————————数据的起始列————————————
    iStartColumn = columns->property("Column").toInt();
}

ExcelOperation::~ExcelOperation()
{
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    if (excel)
    {
        delete excel;
        excel = NULL;
    }

    CoUninitialize();
}

bool ExcelOperation::ExcelCheckFile(QString strPath)
{
    QFile file(strPath);
    if(!file.exists())
    {
        qDebug() << "Not find file name.";
        return false;
    }
    else
    {
        if(!strPath.right(4).contains("xls"))
        {
            qDebug() << "Only operation xlsx、xls";
            return false;
        }
    }

    return true;
}


/**
 * @brief ExcelOperation::ExcelOpenWorkSheet
 * @param sheetName
 * Open sheetName sheet.
 */
QAxObject* ExcelOperation::ExcelOpenWorkSheet(QString userSheetName)
{
    QAxObject *tempWorkShet = NULL;

    for(int i = 1; i <= this->iWorkSheet; i++)
    {
        QAxObject *sheet = this->worksheets->querySubObject("Item(int)", i);
        QString sheetName = sheet->property("Name").toString();
        qDebug() << "SheetName:" << sheetName;
        if(QString::compare(userSheetName, sheetName) == 0)
        {
            tempWorkShet = this->worksheets->querySubObject("Item(int)", i);
            break;
        }
    }

    return tempWorkShet;
}

bool ExcelOperation::ExcelHeadleIsEmpty(void)
{
    if(this->worksheet == NULL)
    {
        qDebug() << "Data is NULL";
        return true;
    }

    return false;
}

//给定的单元格写入
bool ExcelOperation::ExcelWriteExcel(int row, int column, QString msg)
{
    if(ExcelHeadleIsEmpty() == true) return false;

    //—————————————写入数据—————————————
    //获取F6的位置
    //QAxObject *range2 = worksheet->querySubObject("Range(QString)", "F6:F6");

    QAxObject *range2 = worksheet->querySubObject("Cells(int, int)", row, column);


    //写入数据, 第6行，第6列
    range2->setProperty("Value", msg);
    QString newStr = range2->property("Value").toString();
    qDebug() << QString("Write [%1,%2][%3]").arg(row).arg(column).arg(newStr);
    return true;
}

//读取一列
QString ExcelOperation::ExcelReadExcel(int row, int column)
{   
    if(ExcelHeadleIsEmpty() == true) return NULL;

    if(this->iRows + this->iStartRow - 1 < row  || this-> iColumns + this->iStartColumn -1 < column)
    {
        qDebug() << "row or column is error.";
        return NULL;
    }

    //——————————————读出数据—————————————
    //获取第i行第j列的数据
    //假如是第6行，第6列 对应表中F列6行，即F6
    //基于行列的名称读法
    //QAxObject *range1 = worksheet->querySubObject("Range(QString)", "F6:F6");


    //基于坐标的读法
    QAxObject *range1 = worksheet->querySubObject("Cells(int, int)", row, column);
    return range1->property("Value").toString();
}


#if 0
int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QString strPath = QDir::currentPath() + "/key.xlsx" ;

    qDebug() << strPath;

    read_excel(strPath);

    write_excel(strPath, 3, 2);

    //return a.exec();
}
#endif
