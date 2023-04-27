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
                   readBookindexElement();
               }
               else
               {
                   reader.raiseError("Not a valid book file");
               }
           }
           else
           {
               qDebug()<<"111111111111111";
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

void ReadFile::readBookindexElement()
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
               readEntryElement();

           }
           else
           {
               skipUnknownElement();
           }
       }
       else
       {
           reader.readNext();
       }
   }
}


void ReadFile::readEntryElement(void)
{
    Q_ASSERT(reader.isStartElement() && reader.name() == "body");

    reader.readNext();  //</entry>

    while (!reader.atEnd())
    {
        if (reader.isEndElement())
        {
            reader.readNext();
            break;
        }

        if (reader.isStartElement())
        {

            if (reader.name() == "sub-section")
            {
                ReadSubSection();
            }
#if 0
            else if (reader.name() == "page")
            {
                readPageElement();
            }
#endif
            else
            {
                skipUnknownElement();
            }
        }
        else
        {

            reader.readNext();
        }
    }
}


void ReadFile::ReadSubSection(void)
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
            cout << reader.name();
            if (reader.name() == "p")
            {
                ReadSubSection();
            }
            else if(reader.name() == "t")
            {
                cout << reader.attributes().value("wx:val").toString();
            }
            else
            {
                skipUnknownElement();
            }
        }
        else
        {

            reader.readNext();
        }
    }
}

void ReadFile::ReadListPr(void)
{
     Q_ASSERT(reader.isStartElement() && reader.name() == "listPr");
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
            if(reader.name() == "listPr")
            {
                tileFlg = true;
                reader.readNext();
            }
            else if(reader.name() == "t" && tileFlg == true)
            {
                cout << reader.attributes().value("wx:val").toString();
                tileFlg = false;
                reader.readNext();
            }
            else
            {
                skipUnknownElement();
            }
        }
        else
        {

            reader.readNext();
        }
    }
}

void ReadFile::readPageElement(void)
{
    QString page = reader.readElementText();

    if (reader.isEndElement())
    {
        qDebug() <<"3333333333333333";
        reader.readNext();
    }

    QString allPages;
    if (!allPages.isEmpty())
    {
        allPages += ", ";
    }
    allPages += page;
    cout << allPages;
}


void ReadFile::skipUnknownElement()
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
            skipUnknownElement();
            break;
        }
        else
        {
            reader.readNext();

        }
    }
}

