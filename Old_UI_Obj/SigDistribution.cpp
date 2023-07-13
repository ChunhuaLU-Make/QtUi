#include <QDebug>
#include <QString>
#include "SigDistribution.h"
#include "CallPyInterface.h"

SigDistribution::SigDistribution()
{

}

void SigDistribution::RadioButtonFuncDis(RadioBut sel)
{
    CallPyInterface callFunc;

    switch(sel)
    {
    case WordToExcel:
        callFunc.CallPyDocxToExcel(this->filePath.toLatin1().constData());
        break;

    case ExcelToWord:
         callFunc.CallPyExcelToDocx(this->filePath.toLatin1().constData());
        break;

    default:
        qDebug()<< "Not the radio button.";
        break;
    }
}

void SigDistribution::run()
{

    if(filePath.isEmpty())
    {
        MyPrintTest("Error:" + filePath);
        return ;
    }
    MyPrintTest("XmlPaht:" + filePath);

    RadioButtonFuncDis(this->raditFlag);

}

void SigDistribution::MyPrintTest(QString debugInfor)
{
    QString str = debugInfor += '\n';
    emit MyPrintfSig(str);
}


void SigDistribution::RadioInforWtoE()
{
    raditFlag = WordToExcel;
}

void SigDistribution::RadioInforEtoW()
{
    raditFlag = ExcelToWord;
}

void SigDistribution::ReadFileSlot(QString fileName)
{
    this->filePath = fileName;
}




