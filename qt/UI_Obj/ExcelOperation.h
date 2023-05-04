#ifndef EXCELOPERATION_H
#define EXCELOPERATION_H

#include <QString>


class ExcelOperation
{
public:
    ExcelOperation();

    static bool ExcelWriteExcel(QString &path, int row, int column);
    static bool ExcelReadExcel(QString &path);

private:
    static bool ExcelCheckFile(QString &strPath);
};


#endif // EXCELOPERATION_H
