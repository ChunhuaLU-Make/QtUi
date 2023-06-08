#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
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

    int a = 0;

private:
    Ui::MainWindow *ui;
    ReadFile* readXml;
    QTimer *timer = NULL;
    QVector<QString> imp;

private slots:
   void MyPrintf();

};
#endif // MAINWINDOW_H
