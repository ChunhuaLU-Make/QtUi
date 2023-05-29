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
    enum ExcelErrorCode errorCode = ExcelOperation::ExcelCheckFile(path);
    if(EXCEL_NOT_XLSX_OR_XLS == errorCode)
    {
        qDebug() << "Only operation xlsx、xls";
        return;
    }


    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    excel = new QAxObject("Excel.Application");
    excel->dynamicCall("SetVisible(bool)", false);
    workbooks = excel->querySubObject("WorkBooks");
    if(EXCEL_NOT_EXIST == errorCode)
    {
        /* Create a excel. */
       workbooks->dynamicCall("Add");
       workbook = excel->querySubObject("ActiveWorkBook");
       workbook->dynamicCall("SaveAs(const QString&)",path);
       qDebug() << "File not exit, Create new file";
    }
    else
    {
        // Open path file.
        workbook = workbooks->querySubObject("Open(QString&)", path);
    }

    // Get opened excel file all work sheet.
    worksheets = workbook->querySubObject("WorkSheets");

    this->iWorkSheet = worksheets->property("Count").toInt();

    this->worksheet = ExcelOpenWorkSheet(sheetName);
    if(this->worksheet == NULL)
    {
        this->appendSheet(sheetName, 1);
        qDebug() << "Not SheetName:" << sheetName;
    }

    /* Update current row column.*/
    ExcelUpdateRowColu();

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

void ExcelOperation::newExcel(const QString &fileName)
{
    qDebug() << "New excel;";

#if 0
    QAxObject* pApplication = new QAxObject("Excel.Application");
   if (pApplication == nullptr)
   {
       qWarning("pApplication\n");
       return;
   }
   pApplication->dynamicCall("SetVisible(bool)",false);// false不显示窗体
   pApplication->setProperty("DisplayAlerts",false);// 不显示任何警告信息
   QAxObject* pWorkBooks = pApplication->querySubObject("Workbooks");
   QAxObject* pWorkBook = NULL;
   QFile file(fileName);
   if (file.exists() == false)
   {
       qDebug() << "hello error";
       pWorkBooks->dynamicCall("Add");
       pWorkBook = pApplication->querySubObject("ActiveWorkBook");
       pWorkBook->dynamicCall("SaveAs(const QString&)",fileName);
   } else
   {


   }
   QAxObject* pSheets = NULL;//pWorkBook->querySubObject("Sheets");
   QAxObject* pSheet = NULL; //pSheets->querySubObject("Item(int)",1);

   this->excel = pApplication;
   this->workbooks = pWorkBooks;
   this->workbook = pWorkBook;  //Excel操作对象
   this->worksheets = pSheets;
   this->worksheet = pSheet;
#endif

}

/**
 * TODO the interface not test.
 * @brief ExcelOperation::appendSheet
 * @param sheetName
 * @param cnt
 * @return
 */
QAxObject* ExcelOperation::appendSheet(const QString &sheetName,int cnt)
{
    QAxObject* pSheets = this->worksheets;

    QAxObject *pLastSheet = pSheets->querySubObject("Item(int)",cnt);
    pSheets->querySubObject("Add(QVariant)",pLastSheet->asVariant());
    QAxObject* pSheet = pSheets->querySubObject("Item(int)",cnt);
    pLastSheet->dynamicCall("Move(QVariant)",pSheet->asVariant());
    pSheet->setProperty("Name",sheetName);

    return pSheet;
}

/**
 * TODO the interface not test.
 * @brief ExcelOperation::delSheet
 * @param name
 * @return
 */
bool ExcelOperation::delSheet(QString name)
{
    try
    {
        QAxObject *pFirstSheet = worksheets->querySubObject("Item(QString)", name);
        pFirstSheet->dynamicCall("delete");
    }
    catch (...)
    {
        qCritical()<<"删除sheet失败...";
        return false;
    }

    return true;
}

/**
 * TODO the interface not test.
 * @brief ExcelOperation::delSheet
 * @param index
 * @return
 */
bool ExcelOperation::delSheet(int index)
 {
    try
    {
        QAxObject *pFirstSheet = worksheets->querySubObject("Item(int)", index);
        pFirstSheet->dynamicCall("delete");
    }
    catch (...)
    {
        qCritical()<<"删除sheet失败...";
        return false;
    }
    return true;
}

/**
 * TODO the interface not test.
 * @brief ExcelOperation::clearSheet
 * @param name
 * @return
 */
bool ExcelOperation::clearSheet(QString name)
{
    if(this->ExcelOpenWorkSheet(name) == NULL)
    {
        return false;
    }

    if(true == delSheet(name))
    {
        this->worksheet = appendSheet(name, 1);
        return true;
    }

    return false;
}

/**
 * TODO the interface not test.
 * @brief ExcelOperation::clearSheet
 * @param index
 * @return
 */
bool ExcelOperation::clearSheet(int index)
{
    if(index > this->iWorkSheet)
    {
        return false;
    }

    QAxObject *sheet = this->worksheets->querySubObject("Item(int)", index);
    QString sheetName = sheet->property("Name").toString();
    if(true == delSheet(index))
    {
        this->worksheet = appendSheet(sheetName, 1);
        return true;
    }

    return false;
}

void ExcelOperation::ExcelUpdateRowColu(void)
{
    //—————————获取该sheet的数据范围（可以理解为有数据的矩形区域）————
    QAxObject* usedrange = worksheet->querySubObject("UsedRange");

    //———————————————————获取行数———————————————
    QAxObject* rows = usedrange->querySubObject("Rows");
    this->iRows = rows->property("Count").toInt();

    //————————————获取列数—————————
    QAxObject* columns = usedrange->querySubObject("Columns");
    this->iColumns = columns->property("Count").toInt();

    //————————数据的起始行———
    this->iStartRow = rows->property("Row").toInt();

    //————————数据的起始列————————————
    this->iStartColumn = columns->property("Column").toInt();
}

ExcelOperation::ExcelErrorCode ExcelOperation::ExcelCheckFile(QString strPath)
{
    QFile file(strPath);
    if(!file.exists())
    {
        return EXCEL_NOT_EXIST;
    }
    else
    {
        if(!strPath.right(4).contains("xls"))
        {

            return EXCEL_NOT_XLSX_OR_XLS;
        }
    }

    return EXCEL_NORAML;
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


