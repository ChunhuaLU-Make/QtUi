#include "readfile.h"
#include <iostream>
#include <QDebug>
#include <QFile>

#define cout qDebug()<<"["<<__FUNCTION__<<";"<<__LINE__<<"]"

ReadFile::ReadFile()
{

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
               if (reader.name() == "bookindex")
               {
                   readBookindexElement();
                   //readTestCode();
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

void ReadFile::readTestCode(void)
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
                cout << reader.name();  //body
                reader.readNext();
                cout << reader.name();  // ""
                reader.readNext();
                cout << reader.name();   //sub-section
                reader.readNext();
                cout << reader.name();  //""
                reader.readNext();
                cout << reader.name();  //p
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

void ReadFile::readBookindexElement()
{
   Q_ASSERT(reader.isStartElement() && reader.name() == "bookindex");
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
           if (reader.name() == "entry")
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
    Q_ASSERT(reader.isStartElement() && reader.name() == "entry");

    cout << reader.attributes().value("term").toString();

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
            cout << reader.name();

            if (reader.name() == "entry")
            {
                readEntryElement();
            }
            else if (reader.name() == "page")
            {
                readPageElement();
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
             //cout << reader.readElementText();
             //cout << reader.text();
            reader.readNext();

        }
    }
}

