#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPushButton* but = new QPushButton(this);
    but->setText("hello");

    connect(but, &QPushButton::released, this,
            [=]()
            {
                qDebug() << "Hello world:" << a << b;
            }
            );
    qDebug() <<"a" << a;

    this->resize(500,500);
}

void MainWindow::MyPrintf(void)
{
    this->readXml = new ReadFile("E:\\Git\\QtUi\\TestDoc\\TempDocx.xml");

    if(readXml != NULL)
    {
        delete readXml;
    }
}

MainWindow::~MainWindow()
{
    if(readXml != NULL)
    {
        delete readXml;
    }

    delete ui;
}

