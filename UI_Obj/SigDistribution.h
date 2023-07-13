#ifndef SIGNALDISTRIBUTION_H
#define SIGNALDISTRIBUTION_H

#include <QThread>

class SigDistribution:public QThread
{
    Q_OBJECT

    enum RadioBut
    {
        WordToExcel,
        ExcelToWord
    };

public:
    SigDistribution();

    void RadioButtonFuncDis(enum RadioBut sel);

private:
    QString filePath;
    enum RadioBut raditFlag = WordToExcel;
    void MyPrintTest(QString debugInfor);


protected:
    virtual void run(void);


signals:
    void MyPrintfSig(const QString &infor);

public slots:
    void RadioInforWtoE(void);
    void RadioInforEtoW(void);
    void ReadFileSlot(QString fileName);
};

#endif // SIGNALDISTRIBUTION_H
