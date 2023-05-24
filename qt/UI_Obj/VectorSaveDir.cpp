#include "VectorSaveDir.h"
#include "DirLevAnaly.h"



VectorSaveDir::VectorSaveDir(void)
{
    excelFile = new ExcelOperation("E:\\Git\\QtUi\\TestDoc\\testEx.xlsx", "Sheet3");
}

VectorSaveDir::~VectorSaveDir(void)
{
    delete excelFile;
}

void VectorSaveDir::SaveDirToVector(QString inputStr)
{
    static int row = 1;

    DirLevAnaly levAnaly(inputStr.toStdString());
    int dirLev = levAnaly.GetDirLev();
    switch (dirLev)
    {
    case 1:
        tempDir1.push_back(inputStr);
        excelFile->ExcelWriteExcel(row, 1, inputStr);
        break;

    case 2:
        tempDir2.push_back(inputStr);
        excelFile->ExcelWriteExcel(row, 2, inputStr);
        break;

    case 3:
        tempDir3.push_back(inputStr);
        excelFile->ExcelWriteExcel(row, 3, inputStr);
        break;

    case 4:
        tempDir4.push_back(inputStr);
        excelFile->ExcelWriteExcel(row, 4, inputStr);
        break;

    case 5:
        tempDir5.push_back(inputStr);
        excelFile->ExcelWriteExcel(row, 5, inputStr);
        break;

     case 6:
        excelFile->ExcelWriteExcel(row, 6, inputStr);
        break;

    default:
        qDebug() << "Dir is error:" << dirLev;
        break;
    }

    if(dirLev > 0 && dirLev < 7) row++;
}

void VectorSaveDir::SaveDirToLevDir(void)
{


    if(!tempDir1.isEmpty())
    {
        levDir.push_back(tempDir1);
    }

    if(!tempDir2.isEmpty())
    {
        levDir.push_back(tempDir2);
    }

    if(!tempDir3.isEmpty())
    {
        levDir.push_back(tempDir3);
    }

    if(!tempDir4.isEmpty())
    {
        levDir.push_back(tempDir4);
    }

    if(!tempDir5.isEmpty())
    {
        levDir.push_back(tempDir5);
    }

    if(!tempDir6.isEmpty())
    {
        levDir.push_back(tempDir6);
    }

    if(!tempDir7.isEmpty())
    {
        levDir.push_back(tempDir7);
    }

    if(!levDir.isEmpty())
    {
        fileDir.push_back(levDir);
    }

    this->tempDir1.clear();
    this->tempDir2.clear();
    this->tempDir3.clear();
    this->tempDir4.clear();
    this->tempDir5.clear();
    this->tempDir6.clear();
    this->tempDir7.clear();
    this->levDir.clear();

}

void VectorSaveDir::SaveDirToFileDir(void)
{
    this->fileDir.push_back(this->levDir);
}

void VectorSaveDir::MyPrintFileDir(void)
{
    for(int i = 0; i < this->fileDir.size(); i++)
    {
        for(int j = 0; j < this->fileDir[i].size(); j++)
        {
            for(int k = 0; k < fileDir[i][j].size(); k++)
            {
                qDebug() << "Dir[" << i <<"][" << j << "][" << k << "]" << this->fileDir[i][j][k];
            }
        }

    }
}
