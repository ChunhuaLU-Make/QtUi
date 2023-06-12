#include "readfile.h"
#include <iostream>
#include <QDebug>
#include <QFile>
//#include <QtTest>
#include "DirLevAnaly.h"

#define cout qDebug()<<"["<<__FUNCTION__<<";"<<__LINE__<<"]"

#define WRITEFIL() QString hStr=QString("%1").arg(__LINE__); file->write(hStr + reader.name().toUtf8() + '\n')

ReadFile::ReadFile(QString filePath)
{

    file = new QFile("./tempSave.txt");
    bool openOk=file->open(QIODevice::WriteOnly);
    if(!openOk)
    {
        qDebug() << "Open fiel fail";
        file = NULL;
    }

    QFile fileTemp("E:\\Git\\QtUi\\TestDoc\\testEx.xlsx");
    if(fileTemp.exists())
    fileTemp.remove();
    /* Create a excel.*/
    excelFile = new ExcelOperation("E:\\Git\\QtUi\\TestDoc\\testEx.xlsx", "Sheet1");

    /* Excel default start row is 1. */
    row = 1;

    /* Analysis XML. */
    this->readFile(filePath);


    qDebug() <<"++++++++++++++++++++++++++++";
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
    if(file->exists())
    {
        file->close();
    }

    if(excelFile != NULL) delete excelFile;
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
               if (reader.name() == "wordDocument")
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
    Q_ASSERT(reader.isStartElement() && reader.name() == "body");

    while (!reader.atEnd())
    {
       if (reader.isEndElement())
       {
           reader.readNext();
           continue;
       }

       if (reader.isStartElement())
       {
           if (reader.name() == "sub-section")
           {
               cout << reader.name();
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
    Q_ASSERT(reader.isStartElement() && reader.name() == "wordDocument");
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
           if (reader.name() == "body")
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
    QStringRef rderName = reader.name();
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
    Q_ASSERT(reader.isStartElement() && reader.name() == "sub-section");
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
            QStringRef rderName = reader.name();
            if(rderName == 'p')
            {
                QString str;
                str.clear();
                ReadP(str);

                /* Save data to excel.*/
                this->ReadFileSaveToExcel(str);

                str += '\n';
                file->write(str.toUtf8());
                // qDebug() << str;

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

