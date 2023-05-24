#ifndef READFILE_H
#define READFILE_H
#include <QXmlStreamReader>
#include <QFile>
#include <QVector>
#include "ExcelOperation.h"

class ReadFile
{

public:
    ReadFile(QString filePath);
    ~ReadFile();
    bool readFile(const QString &fileName);

private:
    int subSectionCont = 0;
    int k = 0, i = 0;
    int row = 0;
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
