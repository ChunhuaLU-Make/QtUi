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
    int iWorkSheet = 0; /* Excel�ļ��б�ĸ��� */
    int iRows = 0;      //��ȡ����
    int iColumns = 0;   //��ȡ����
    int iStartRow = 0;  //���ݵ���ʼ��
    int iStartColumn = 0;   //���ݵ���ʼ��

    ExcelOperation();
    ~ExcelOperation();

    void newExcel(const QString &fileName);// �½�һ��excel
    QAxObject* appendSheet(const QString &sheetName,int cnt);// ����һ��worksheet
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
    QAxObject *excel = NULL;    //�����У�excel�趨ΪExcel�ļ��Ĳ�������
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;  //Excel��������
    QAxObject * worksheets = NULL;
    QAxObject * worksheet = NULL;


    enum ExcelErrorCode ExcelCheckFile(QString strPath);

    QAxObject* ExcelOpenWorkSheet(QString sheetName);

    bool ExcelHeadleIsEmpty(void);

};


#endif // EXCELOPERATION_H


