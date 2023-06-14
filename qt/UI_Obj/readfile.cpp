#include "readfile.h"
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
//#include <QtTest>
#include "DirLevAnaly.h"

#define cout qDebug()<<"["<<__FUNCTION__<<";"<<__LINE__<<"]"

#define WRITEFIL() QString hStr=QString("%1").arg(__LINE__); file->write(hStr + reader.name().toUtf8() + '\n')

ReadFile::ReadFile()
{
    /* Open log file. */
    file = this->ReadFileOpenLogFile();
}

void ReadFile::ReadFileSlot(QString str)
{
    /* Save xml file path. */
    filePath = str;
}


bool ReadFile::ReadFileIsFile(QString fileName)
{
    QFileInfo fileInfo(fileName);
    return fileInfo.isFile();
}

void ReadFile::ReadFileCall(QString filePath)
{
    QFileInfo fileInfo(filePath);
    QString excelPath = fileInfo.absolutePath() + "/testEx.xlsx";
    qDebug() << "excelPath:" << excelPath;

    excelPath = "D:\\lgx\\Temp\\Qt\\QtUi-main\\QtUi-main\\TestDoc\\testEx.xlsx";

    QFile fileTemp(excelPath);
    if(fileTemp.exists())
        fileTemp.remove();

    /* Create a excel objec.*/
    excelFile = new ExcelOperation();

    /* Open excel.*/
    excelFile->ExcelOpen(excelPath, "Sheet1");

    /* Excel default start row is 1. */
    row = 1;

    /* Analysis XML. ans save data to excel.*/
    this->readFile(filePath);

    /* Close excel.*/
    excelFile->ExcelClose();

    MyPrintf("+++++++++++++END+++++++++++++++");
    MyPrintf("+++++++++++++END+++++++++++++++");
    MyPrintf("+++++++++++++END+++++++++++++++");
    MyPrintf("+++++++++++++END+++++++++++++++");
    //this->MyPrintFileDir();
}

void ReadFile::ReadeNameWF(QString infor, int lineNumber)
{
    QString tStr = QString("Line:%1").arg(lineNumber) + "->";
    tStr += infor;
    tStr += ' ';
    tStr += reader.name();
    tStr += '\n';
    if(file->exists())
    {
        file->write(tStr.toUtf8());
    }
    else
    {
        cout << "File not exit.";
    }
}

ReadFile::~ReadFile()
{
    /* Close log file.*/
    this->ReadFileCloseLogFile(this->file);

    //delete this->file;
    delete this->excelFile;
}

bool ReadFile::readFile(const QString &fileName)
{
    QFile file(fileName);
       if (!file.open(QFile::ReadOnly | QFile::Text))
       {
           cout << "Open file error";
           return false;
       }
       reader.setDevice(&file);
       while (!reader.atEnd())
       {
           if (reader.isStartElement())
           {
               if (reader.name().toString() == "wordDocument")
               {
                   ReadBody();
               }
               else
               {
                   reader.raiseError("Not a valid book file");
               }
           }
           else
           {
               reader.readNext();
           }
       }
       file.close();
       if (reader.hasError())
       {
           cout << "Failed to parse file %1";
           return false;
       }
       else if (file.error() != QFile::NoError)
       {
           cout << "Cannot read file %1";
           return false;
       }
       return true;

}


void ReadFile::ReadSubSection(void)
{
    Q_ASSERT(reader.isStartElement() && reader.name().toString() == "body");

    while (!reader.atEnd())
    {
       if (reader.isEndElement())
       {
           reader.readNext();
           continue;
       }

       if (reader.isStartElement())
       {
           if (reader.name().toString() == "sub-section")
           {
               cout << reader.name().toString();
               StartReadData();
           }
           else
           {
               reader.readNext();
           }
       }
       else
       {
           reader.readNext();
       }
    }
}

void ReadFile::ReadBody(void)
{
    Q_ASSERT(reader.isStartElement() && reader.name().toString() == "wordDocument");
    reader.readNext();
    while (!reader.atEnd())
    {
       if (reader.isEndElement())
       {
           reader.readNext();
           break;
       }
       if (reader.isStartElement())
       {
           if (reader.name().toString() == "body")
           {
               ReadSubSection();
           }
           else
           {
               SkipUnknownElement();
           }
       }
       else
       {
           reader.readNext();
       }
    }
}


bool ReadFile::AnalyseData(QString& str)
{
    static bool listPrFlg = false;
    QString rderName = reader.name().toString();
    if(rderName == "listPr")
    {
        //Set title flag.
        listPrFlg = true;
    }
    else if(listPrFlg == true && rderName == 't')
    {
        //Read attribute.
        str += reader.attributes().value("wx:val").toString();
        listPrFlg = false;
    }

    if(rderName == 't')
    {
        str += reader.readElementText();
        if(reader.isEndElement())
        {
            reader.readNext();
            return true;
        }
    }

    return false;
}

void ReadFile::ReadP(QString& str)
{
    reader.readNext();
    while (!reader.atEnd())
    {
        if (reader.isEndElement())
        {
            reader.readNext();
            break;
        }

        if (reader.isStartElement())
        {
            if(AnalyseData(str) == false)
            {
                ReadP(str);
            }
        }
        else
        {
            reader.readNext();

        }

    }
}

void ReadFile::StartReadData(void)
{
    Q_ASSERT(reader.isStartElement() && reader.name().toString() == "sub-section");
    reader.readNext();
    while (!reader.atEnd())
    {
        if (reader.isEndElement())
        {
            reader.readNext();
            break;
        }

        if (reader.isStartElement())
        {
            QString rderName = reader.name().toString();
            if(rderName == 'p')
            {
                QString str;
                str.clear();
                ReadP(str);

                /* Save data to excel.*/
                this->ReadFileSaveToExcel(str);
                MyPrintf(str);
            }
            else if(rderName == "sub-section")
            {
                qDebug() << "------------------";
                StartReadData();
            }
            else
            {
                SkipUnknownElement();
            }
        }
        else
        {
            reader.readNext();

        }
    }
}


void ReadFile::SkipUnknownElement(void)
{
    reader.readNext();
    while (!reader.atEnd())
    {
        if (reader.isEndElement())
        {
            reader.readNext();
            break;
        }

        if (reader.isStartElement())
        {
            SkipUnknownElement();
        }
        else
        {
            reader.readNext();

        }
    }
}

/**
 * @brief ReadFile::ReadFileSaveToExcel
 * @param inputStr docx dir string.
 * Save dir to excel. die level max is 6.
 */
void ReadFile::ReadFileSaveToExcel(QString inputStr)
{
    DirLevAnaly levAnaly(inputStr.toStdString());
    int dirLev = levAnaly.GetDirLev();
    if(dirLev != 0)
    {
        excelFile->ExcelWriteExcel(row, dirLev, inputStr);
        row++;
    }
}

void ReadFile::MyPrintf(QString debugInfor)
{
    QString str = debugInfor += '\n';

    emit MyPrintfSig(str);
    file->write(str.toUtf8());
}

/**
 * Open a text file, if file not exist,Create it.
 * @brief ReadFile::OpenLogFile
 * @return QFile
 */
QFile* ReadFile::ReadFileOpenLogFile(void)
{
    QFile* tempFile = new QFile("./tempSave.txt");
    bool openOk=tempFile->open(QIODevice::WriteOnly);
    if(!openOk)
    {
        MyPrintf("Open fiel fail");
        tempFile = NULL;
    }
    return tempFile;
}

void ReadFile::ReadFileCloseLogFile(QFile* fileHandle)
{
    if(fileHandle != NULL)
    {
        fileHandle->close();
        delete fileHandle;
    }
}


void ReadFile::run(void)
{
#if 1
    if(filePath.isEmpty())
    {
        MyPrintf("Error:" + filePath);
        return ;
    }
    MyPrintf("XmlPaht:" + filePath);
    ReadFileCall(filePath);
#else

    xcelPath = "D:\\lgx\\Temp\\Qt\\QtUi-main\\QtUi-main\\TestDoc\\testEx.xlsx";

    QFile fileTemp(excelPath);
    if(fileTemp.exists())
        fileTemp.remove();

    /* Create a excel.*/
    excelFile = new ExcelOperation(excelPath, "Sheet1");

    /* Excel default start row is 1. */
    row = 1;

#endif
}

