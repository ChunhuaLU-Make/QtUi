#ifndef EXCELOPERATION_H
#define EXCELOPERATION_H

#include <QString>
#include <QAxObject>

class ExcelOperation
{
public:
    int iWorkSheet = 0; /* Excel文件中表的个数 */
    int iRows = 0;      //获取行数
    int iColumns = 0;   //获取列数
    int iStartRow = 0;  //数据的起始行
    int iStartColumn = 0;   //数据的起始列

    ExcelOperation(QString path, QString sheetName);
    ~ExcelOperation();

    bool ExcelWriteExcel(int row, int column, QString msg);
    QString ExcelReadExcel(int row, int column);

    void ExcelUpdateRowColu(void);

private:
    QAxObject *excel = NULL;    //本例中，excel设定为Excel文件的操作对象
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;  //Excel操作对象
    QAxObject * worksheets = NULL;
    QAxObject * worksheet = NULL;


    bool ExcelCheckFile(QString strPath);

    QAxObject* ExcelOpenWorkSheet(QString sheetName);

    bool ExcelHeadleIsEmpty(void);

};


#endif // EXCELOPERATION_H
