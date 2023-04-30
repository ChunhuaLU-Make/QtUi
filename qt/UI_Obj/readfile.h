#ifndef READFILE_H
#define READFILE_H
#include <QXmlStreamReader>
#include <QFile>

class ReadFile
{
public:
    ReadFile();
    ~ReadFile();
    bool readFile(const QString &fileName);

private:
    int subSectionCont = 0;
    int k = 0, i = 0;
    bool titleFlg = false;

    QFile* file = NULL;

    void WriteTextToFile(QString text);
    void ReadeNameWF(QString infor, int lineNumber);
    void ReadP(QString& str);

    void ReadBody(void);
    void ReadSubSection(void);
    void SkipUnknownElement(void);

    void StartReadData(void);
    QXmlStreamReader reader;

    bool tileFlg;
};

#endif // XMLREAGER_H
