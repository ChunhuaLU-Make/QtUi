#include "readfile.h"
#include <iostream>
#include <QDebug>
#include <QFile>

#define cout qDebug()<<"["<<__FUNCTION__<<";"<<__LINE__<<"]"

ReadFile::ReadFile()
{
    tileFlg = false;
}

ReadFile::~ReadFile()
{

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

void ReadFile::ReadP(QString& str)
{
    static bool titleFlg = false;

    reader.readNext();
    while (!reader.atEnd() && reader.name() != "p")
    {
        if (reader.isEndElement())
        {
            cout << reader.name();
            reader.readNext();
            break;
        }

        if (reader.isStartElement())
        {
            cout << reader.name();
            if(reader.name() == "listPr")
            {
                titleFlg = true;
            }
            else if(titleFlg == true && reader.name() == "t")
            {
                //str += reader.attributes().value("wx:val").toString();
                cout << reader.attributes().value("wx:val").toString();
                titleFlg = false;
            }
            else if(reader.name() == "t")
            {
                //str += reader.readElementText();
                cout << reader.readElementText();
            }
            ReadP(str);
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
            cout << reader.name();
            reader.readNext();
            break;
        }

        if (reader.isStartElement())
        {
            //TODO
            if(reader.name() == "p")
            {
                QString str;
                ReadP(str);
                //cout << str;
            }
            StartReadData();
        }
        else
        {
            reader.readNext();

        }
    }
}

