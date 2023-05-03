#ifndef READFILE_H
#define READFILE_H
#include <QXmlStreamReader>
#include <QFile>
#include <QVector>
#include "VectorSaveDir.h"

class ReadFile:public VectorSaveDir
{
public:
    ReadFile(QString filePath);
    ~ReadFile();
    bool readFile(const QString &fileName);

private:
    int subSectionCont = 0;
    int k = 0, i = 0;
    bool titleFlg = false;

    QFile* file = NULL;
    QVector<QVector<QString>> fileDir;

    void ReadeNameWF(QString infor, int lineNumber);
    void ReadP(QString& str);

    void ReadBody(void);
    void ReadSubSection(void);
    void SkipUnknownElement(void);
    bool AnalyseData(QString& str);

    void StartReadData(void);
    QXmlStreamReader reader;

};

#endif // XMLREAGER_H
