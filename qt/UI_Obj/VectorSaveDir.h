#ifndef VECTORSAVEDIR_H
#define VECTORSAVEDIR_H

#include <QString>
#include <QVector>
#include <QDebug>
#include "ExcelOperation.h"

class VectorSaveDir
{
public:
    VectorSaveDir(void);
    ~VectorSaveDir(void);

    void SaveDirToVector(QString tepStr);

    void SaveDirToLevDir(void);

    void SaveDirToFileDir(void);

    void MyPrintFileDir(void);

    QVector<QVector<QVector<QString>>> fileDir;

private:
    ExcelOperation* excelFile = NULL;
    QVector<QVector<QString>> levDir;


    QVector<QString> tempDir1;
    QVector<QString> tempDir2;
    QVector<QString> tempDir3;
    QVector<QString> tempDir4;
    QVector<QString> tempDir5;
    QVector<QString> tempDir6;
    QVector<QString> tempDir7;

};

#endif // VECTORSAVEDIR_H
