#include "ExcelOperation.h"


#include <QFile>
#include <QDir>
#include <QObject>
#include <QString>
#include <QDebug>

#if defined(Q_OS_WIN)
#include <QAxObject>
#include <windows.h>
#endif // Q_OS_WIN
#include <QVariant>


ExcelOperation::ExcelOperation()
{

}


bool ExcelOperation::ExcelCheckFile(QString &strPath)
{
    QFile file(strPath);
    if(!file.exists())
    {
        qDebug() << "Not find file name.";
        return false;
    }
    else
    {

        //�ļ����ʹ��Լ��
        if(!strPath.right(4).contains("xls"))
        {
            qDebug() << "Only operation xlsx��xls";
            return false;
        }
    }

    return true;
}

//�����ĵ�Ԫ��д��
bool ExcelOperation::ExcelWriteExcel(QString &path, int row, int column)
{
    if(false == ExcelOperation::ExcelCheckFile(path))
    {
        return false;
    }

    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    QAxObject *excel = NULL;    //�����У�excel�趨ΪExcel�ļ��Ĳ�������
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;  //Excel��������
    excel = new QAxObject("Excel.Application");
    excel->dynamicCall("SetVisible(bool)", false); //true ��ʾ�����ļ�ʱ�ɼ���false��ʾΪ���ɼ�
    workbooks = excel->querySubObject("WorkBooks");


    //�����������������������������������ļ�·�����ļ�����������������������������������������
    workbook = workbooks->querySubObject("Open(QString&)", path);
    // ��ȡ�򿪵�excel�ļ������еĹ���sheet
    QAxObject * worksheets = workbook->querySubObject("WorkSheets");


    //����������������������������������Excel�ļ��б�ĸ���:������������������������������������
    int iWorkSheet = worksheets->property("Count").toInt();
    qDebug() << QString("Excel�ļ��б�ĸ���: %1").arg(QString::number(iWorkSheet));


    // ����������������������������������ȡ��n�������� querySubObject("Item(int)", n);��������������������
    QAxObject * worksheet = worksheets->querySubObject("Item(int)", 1);//������ȡ��һ������������1


    //��������������������������д�����ݡ�������������������������
    //��ȡF6��λ��
    //QAxObject *range2 = worksheet->querySubObject("Range(QString)", "F6:F6");

    QAxObject *range2 = worksheet->querySubObject("Cells(int, int)", column , row);


    //д������, ��6�У���6��
    range2->setProperty("Value", "macdcci");
    QString newStr = "";
    newStr = range2->property("Value").toString();
    qDebug() << "д�����ݺ󣬵�6�У���6�е�����Ϊ��" + newStr;

    //!!!!!!!һ��Ҫ�ǵ�close����Ȼϵͳ����������n��EXCEL.EXE����
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    if (excel)
    {
        delete excel;
        excel = NULL;
    }

    CoUninitialize();

    return true;

}

//��ȡһ��
bool ExcelOperation::ExcelReadExcel(QString &path)
{
    if(false == ExcelOperation::ExcelCheckFile(path))
    {
        return false;
    }

    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    QAxObject *excel = NULL;    //�����У�excel�趨ΪExcel�ļ��Ĳ�������
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;  //Excel��������
    excel = new QAxObject("Excel.Application");
    excel->dynamicCall("SetVisible(bool)", false); //true ��ʾ�����ļ�ʱ�ɼ���false��ʾΪ���ɼ�
    workbooks = excel->querySubObject("WorkBooks");


    //�����������������������������������ļ�·�����ļ�����������������������������������������
    workbook = workbooks->querySubObject("Open(QString&)", path);
    // ��ȡ�򿪵�excel�ļ������еĹ���sheet
    QAxObject * worksheets = workbook->querySubObject("WorkSheets");


    //����������������������������������Excel�ļ��б�ĸ���:������������������������������������
    int iWorkSheet = worksheets->property("Count").toInt();
    qDebug() << QString("Excel�ļ��б�ĸ���: %1").arg(QString::number(iWorkSheet));


    // ����������������������������������ȡ��n�������� querySubObject("Item(int)", n);��������������������
    QAxObject * worksheet = worksheets->querySubObject("Item(int)", 1);//������ȡ��һ������������1


    //��������������������ȡ��sheet�����ݷ�Χ���������Ϊ�����ݵľ������򣩡�������
    QAxObject * usedrange = worksheet->querySubObject("UsedRange");

    //����������������������������������������ȡ����������������������������������
    QAxObject * rows = usedrange->querySubObject("Rows");
    int iRows = rows->property("Count").toInt();
    qDebug() << QString("����Ϊ: %1").arg(QString::number(iRows));

    //��������������������������ȡ����������������������
    QAxObject * columns = usedrange->querySubObject("Columns");
    int iColumns = columns->property("Count").toInt();
    qDebug() << QString("����Ϊ: %1").arg(QString::number(iColumns));

    //�������������������ݵ���ʼ�С�����
    int iStartRow = rows->property("Row").toInt();
    qDebug() << QString("��ʼ��Ϊ: %1").arg(QString::number(iStartRow));

    //�������������������ݵ���ʼ�С�����������������������
    int iColumn = columns->property("Column").toInt();
    qDebug() << QString("��ʼ��Ϊ: %1").arg(QString::number(iColumn));


    //�����������������������������������ݡ�������������������������
    //��ȡ��i�е�j�е�����
    //�����ǵ�6�У���6�� ��Ӧ����F��6�У���F6
    //�������е����ƶ���
    //QAxObject *range1 = worksheet->querySubObject("Range(QString)", "F6:F6");



    //��������Ķ���
    QAxObject *range1 = worksheet->querySubObject("Cells(int, int)", 2 , 1);
    QString strRow6Col6 = range1->property("Value").toString();
    qDebug() << "The 6line data is:" + strRow6Col6;


    //��ȡһ��


    QString temp;
    int i = 1;

    for (; i <= iRows ; i ++)
    {
        range1 = worksheet->querySubObject("Cells(int, int)", i , 2);

        qDebug() <<  range1->property("Value").toString() << Qt::endl;
    }

    //�����һ��ת������������6�У���6�У�66תΪF6
    //!!!!!!!һ��Ҫ�ǵ�close����Ȼϵͳ����������n��EXCEL.EXE����
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    if (excel)
    {
        delete excel;
        excel = NULL;
    }

    CoUninitialize();

    return true;
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
