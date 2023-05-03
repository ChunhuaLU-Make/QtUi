#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "readfile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void MyPrintf();

private:
    Ui::MainWindow *ui;
    ReadFile* readXml;


private slots:
    //void MyPrintf();

};
#endif // MAINWINDOW_H
