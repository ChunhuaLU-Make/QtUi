#include "readfile.h"
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QtTest>

#define cout qDebug()<<"["<<__FUNCTION__<<";"<<__LINE__<<"]"

#define WRITEFIL() QString hStr=QString("%1").arg(__LINE__); file->write(hStr + reader.name().toUtf8() + '\n')

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

ReadFile::ReadFile()
{
    file = new QFile("./tempSave.txt");
    bool openOk=file->open(QIODevice::WriteOnly);
    if(!openOk)
    {
        qDebug() << "Open fiel fail";
        file = NULL;
    }
    tileFlg = false;
}

ReadFile::~ReadFile()
{
    if(file->exists())
    {
        file->close();
    }
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
        reader.readNext();

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
    else if(rderName == 't')
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
                str += '\n';
                file->write(str.toUtf8());
            }
            else if(rderName == "sub-section")
            {
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

