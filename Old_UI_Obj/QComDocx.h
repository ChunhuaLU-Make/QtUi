#ifndef QCOMDOCX_H
#define QCOMDOCX_H

#include <QStyleFactory>
#include <QAxWidget>
#include <QAxObject>
#include <QTextDocument>
#include <QDebug>

namespace Ui {
class QWord;
}

class QWord
{

public:
    explicit QWord();
    ~QWord();

    static bool ExportHtml(const QString &filePath, const QTextDocument &document);

private slots:
    void on_createButton_clicked();

    void on_readButton_clicked();

    void on_writeButton_clicked();

};

#endif // QWORD_H
