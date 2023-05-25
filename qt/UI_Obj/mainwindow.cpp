#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked,this, &MainWindow::MyPrintf);

    this->readXml = NULL;
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

