#include "readfile.h"
#include <iostream>
#include <QDebug>
#include <QFile>

#define cout qDebug()<<"["<<__FILE__<<";"<<__LINE__<<"]"

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

           if (reader.isStartElement()) //检测当前读取类型
           {
               //if (reader.name() == "bookindex")

               if(reader.name() == "root")
               {
                   readBookindexElement();//递归下降算法，层层读取
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
               reader.readNext(); //循坏调用首次移动3次，后面移动一次
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
    Q_ASSERT(reader.isStartElement() && reader.name() == "wordDocument");//不是则会报错
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
   Q_ASSERT(reader.isStartElement() && reader.name() == "root");//不是则会报错
   reader.readNext(); // 读取下一个记号，它返回记号的类型
   while (!reader.atEnd())
   {
       if (reader.isEndElement())
       {
           reader.readNext();
           break;
       }

       if (reader.isStartElement())
       {
           if (reader.name() == "man")
           {
               /* 一个章节的开始。 */
               //readEntryElement();
               readChapter();
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

void ReadFile::readChapter(void)
{
    Q_ASSERT(reader.isStartElement() && reader.name() == "body");//不是则会报错
    reader.readNext(); // 读取下一个记号，它返回记号的类型
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
                /* 一个章节的开始。 */
                //readEntryElement();
                ReadParagraph();
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



void ReadFile::ReadParagraph(void)
{
    Q_ASSERT(reader.isStartElement() && reader.name() == "sub-section");//不是则会报错
    reader.readNext(); // 读取下一个记号，它返回记号的类型
    while (!reader.atEnd())
    {
        if (reader.isEndElement())
        {
            reader.readNext();
            break;
        }

        if (reader.isStartElement())
        {
            if (reader.name() == "p")
            {
                /* 开始一个段落。 */
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
    Q_ASSERT(reader.isStartElement() && reader.name() == "p");//不是则会报错

    //cout << reader.attributes().value("wx:val").toString();

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

            if (reader.name() == "wx:t")
            {
                readEntryElement();
            }
            else if (reader.name() == "w:t")
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
        }
        else
        {
            reader.readNext();
        }
    }
}

