#ifndef READFILE_H
#define READFILE_H
#include <QXmlStreamReader>
#include <QFile>
#include <QVector>
#include <QThread>
#include "ExcelOperation.h"

class ReadFile:public QThread
{
    Q_OBJECT

public:
    ReadFile();
    ~ReadFile();
    bool readFile(const QString &fileName);

    void ReadFileCall(QString filePath);
    bool ReadFileIsFile(QString fileName);

private:
    int subSectionCont = 0;
    int k = 0, i = 0;
    int row = 0;
    bool titleFlg = false;

    QString filePath;

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

    void MyPrintf(QString debugInfor);

    QFile* ReadFileOpenLogFile(void);
    void ReadFileCloseLogFile(QFile* fileHandle);

protected:
    virtual void run(void);

signals:
    void MyPrintfSig(const QString &infor);

public slots:
    void ReadFileSlot(QString str);

};

#endif // XMLREAGER_H
