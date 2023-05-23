#ifndef EXCELOPERATION_H
#define EXCELOPERATION_H

#include <QString>
#include <QAxObject>

class ExcelOperation
{
public:
    int iWorkSheet = 0; /* Excel�ļ��б�ĸ��� */
    int iRows = 0;      //��ȡ����
    int iColumns = 0;   //��ȡ����
    int iStartRow = 0;  //���ݵ���ʼ��
    int iStartColumn = 0;   //���ݵ���ʼ��

    ExcelOperation(QString path, QString sheetName);
    ~ExcelOperation();

    bool ExcelWriteExcel(int row, int column, QString msg);
    QString ExcelReadExcel(int row, int column);

    void ExcelUpdateRowColu(void);

private:
    QAxObject *excel = NULL;    //�����У�excel�趨ΪExcel�ļ��Ĳ�������
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;  //Excel��������
    QAxObject * worksheets = NULL;
    QAxObject * worksheet = NULL;


    bool ExcelCheckFile(QString strPath);

    QAxObject* ExcelOpenWorkSheet(QString sheetName);

    bool ExcelHeadleIsEmpty(void);

};


#endif // EXCELOPERATION_H
