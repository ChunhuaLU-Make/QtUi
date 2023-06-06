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

    int a = 100, b = 200;

private:
    Ui::MainWindow *ui;
    ReadFile* readXml;

protected:
    void paintEvent(QPaintEvent* tempP);

private slots:
   void MyPrintf();

};
#endif // MAINWINDOW_H
