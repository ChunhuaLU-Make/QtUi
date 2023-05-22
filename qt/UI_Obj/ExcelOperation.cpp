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

    //��������������������ȡ��sheet�����ݷ�Χ���������Ϊ�����ݵľ������򣩡�������
    QAxObject* usedrange = worksheet->querySubObject("UsedRange");

    //����������������������������������������ȡ����������������������������������
    QAxObject* rows = usedrange->querySubObject("Rows");
    iRows = rows->property("Count").toInt();

    //��������������������������ȡ����������������������
    QAxObject* columns = usedrange->querySubObject("Columns");
    iColumns = columns->property("Count").toInt();

    //�������������������ݵ���ʼ�С�����
    iStartRow = rows->property("Row").toInt();

    //�������������������ݵ���ʼ�С�����������������������
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
            qDebug() << "Only operation xlsx��xls";
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

//�����ĵ�Ԫ��д��
bool ExcelOperation::ExcelWriteExcel(int row, int column, QString msg)
{
    if(ExcelHeadleIsEmpty() == true) return false;

    //��������������������������д�����ݡ�������������������������
    //��ȡF6��λ��
    //QAxObject *range2 = worksheet->querySubObject("Range(QString)", "F6:F6");

    QAxObject *range2 = worksheet->querySubObject("Cells(int, int)", row, column);


    //д������, ��6�У���6��
    range2->setProperty("Value", msg);
    QString newStr = range2->property("Value").toString();
    qDebug() << QString("Write [%1,%2][%3]").arg(row).arg(column).arg(newStr);
    return true;
}

//��ȡһ��
QString ExcelOperation::ExcelReadExcel(int row, int column)
{   
    if(ExcelHeadleIsEmpty() == true) return NULL;

    if(this->iRows + this->iStartRow - 1 < row  || this-> iColumns + this->iStartColumn -1 < column)
    {
        qDebug() << "row or column is error.";
        return NULL;
    }

    //�����������������������������������ݡ�������������������������
    //��ȡ��i�е�j�е�����
    //�����ǵ�6�У���6�� ��Ӧ����F��6�У���F6
    //�������е����ƶ���
    //QAxObject *range1 = worksheet->querySubObject("Range(QString)", "F6:F6");


    //��������Ķ���
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
