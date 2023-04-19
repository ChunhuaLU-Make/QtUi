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
    void ReadParagraphNext(void);
    void readTestCode(void);
    void readChapter(void);
    void ReadParagraph(void);
    void readBookindexElement();
    void readEntryElement(void);
    void readPageElement(void);
    void skipUnknownElement(void);
    QXmlStreamReader reader;
};

#endif // XMLREAGER_H
