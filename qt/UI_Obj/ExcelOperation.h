#ifndef EXCELOPERATION_H
#define EXCELOPERATION_H

#include <QString>
#include <QAxObject>
#include <QObject>

class ExcelOperation:public QObject
{
    enum ExcelErrorCode
    {
        EXCEL_NORAML,
        EXCEL_NOT_EXIST,
        EXCEL_NOT_XLSX_OR_XLS
    };

public:
    int iWorkSheet = 0; /* Excel文件中表的个数 */
    int iRows = 0;      //获取行数
    int iColumns = 0;   //获取列数
    int iStartRow = 0;  //数据的起始行
    int iStartColumn = 0;   //数据的起始列

    ExcelOperation();
    ~ExcelOperation();

    void newExcel(const QString &fileName);// 新建一个excel
    QAxObject* appendSheet(const QString &sheetName,int cnt);// 增加一个worksheet
    bool delSheet(QString name);
    bool delSheet(int index);
    bool clearSheet(QString name);
    bool clearSheet(int index);
    bool ExcelWriteExcel(int row, int column, QString msg);
    QString ExcelReadExcel(int row, int column);

    void ExcelUpdateRowColu(void);

    void ExcelOpen(QString path, QString sheetName);
    void ExcelClose(void);

private:
    QAxObject *excel = NULL;    //本例中，excel设定为Excel文件的操作对象
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;  //Excel操作对象
    QAxObject * worksheets = NULL;
    QAxObject * worksheet = NULL;


    enum ExcelErrorCode ExcelCheckFile(QString strPath);

    QAxObject* ExcelOpenWorkSheet(QString sheetName);

    bool ExcelHeadleIsEmpty(void);

};


#endif // EXCELOPERATION_H


