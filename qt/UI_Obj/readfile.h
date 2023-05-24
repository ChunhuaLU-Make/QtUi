#ifndef READFILE_H
#define READFILE_H
#include <QXmlStreamReader>
#include <QFile>
#include <QVector>
#include "ExcelOperation.h"

class ReadFile
{
    enum
    {
        DIR_LEVE1 = 1,
        DIR_LEVE2,
        DIR_LEVE3,
        DIR_LEVE4,
        DIR_LEVE5,
        DIR_LEVE6,
        DIR_LEVE_MAX
    };

public:
    ReadFile(QString filePath);
    ~ReadFile();
    bool readFile(const QString &fileName);

private:
    int subSectionCont = 0;
    int k = 0, i = 0;
    bool titleFlg = false;

    QFile* file = NULL;
    ExcelOperation* excelFile = NULL;

    void ReadeNameWF(QString infor, int lineNumber);
    void ReadP(QString& str);

    void ReadBody(void);
    void ReadSubSection(void);
    void SkipUnknownElement(void);
    bool AnalyseData(QString& str);

    void StartReadData(void);
    QXmlStreamReader reader;

    void ReadFileSaveToExcel(QString inputStr);

};

#endif // XMLREAGER_H
