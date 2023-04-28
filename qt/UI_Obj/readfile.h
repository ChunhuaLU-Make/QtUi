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
    int subSectionCont = 0;
    void ReadP(QString& str);
    void StartReadData(void);
    QXmlStreamReader reader;

    bool tileFlg;
};

#endif // XMLREAGER_H
