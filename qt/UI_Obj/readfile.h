#ifndef READFILE_H
#define READFILE_H
#include <QXmlStreamReader>

class ReadFile
{
public:
    ReadFile();
    ~ReadFile();
    bool readFile(const QString &fileName);
private:
    void ReadListPr(void);
    void ReadText(void);
    void ReadSubSection(void);
    void ReadParagraphNext(void);
    void readChapter(void);
    void ReadParagraph(void);
    void readBookindexElement();
    void readEntryElement(void);
    void readPageElement(void);
    void skipUnknownElement(void);
    QXmlStreamReader reader;

    bool tileFlg;
};

#endif // XMLREAGER_H
