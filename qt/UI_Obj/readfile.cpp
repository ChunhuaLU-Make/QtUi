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



void ReadFile::WriteTextToFile(QString fText)
{
    file->write(fText.toUtf8());
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
                   StartReadData();
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
    reader.readNext();
    while (!reader.atEnd())
    {
       if (reader.isEndElement())
       {
           reader.readNext();
           break;
       }

       cout << reader.name();
       if (reader.isStartElement())
       {
           if (reader.name() == "sub-section")
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

       cout << reader.name();
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

void ReadFile::StartReadData(void)
{
    reader.readNext();
    while (!reader.atEnd())
    {
        if (reader.isEndElement())
        {
            //ReadeNameWF("Exit", __LINE__);
            //cout << reader.name();
            if(reader.name() == 'p')
            {
                WriteTextToFile("\n");
            }
            reader.readNext();
            break;
        }

        if (reader.isStartElement())
        {
            //cout << reader.name();
            //ReadeNameWF("Input", __LINE__);
            QString str;
            str.clear();
            QString readName = reader.name().toString();
            if(readName == "listPr")
            {
                titleFlg = true;
            }
            else if(titleFlg == true && readName == "t")
            {
                str += reader.attributes().value("wx:val").toString();
                titleFlg = false;
            }
            else if(readName == "t")
            {
                //str += reader.text().toString();

                str += reader.readElementText();
                if(reader.isEndElement())
                {
                    reader.readNext();
                }

goto target;

            }

            i++;
            StartReadData();
            k++;
            if(file != NULL)
            {
                QString str = QString("xmlLin:%1 k:%2, i:%3").arg(reader.columnNumber()).arg(k).arg(i);
                str += '\n';
                //file->write(str.toUtf8());
                //QString str = "K:" << k <<','<< "i:"<<i;
            }
            else
            {
                qDebug()<<"File is error";
            }
target:
            if(str.isNull() == false)
            {
                 WriteTextToFile(str);
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

