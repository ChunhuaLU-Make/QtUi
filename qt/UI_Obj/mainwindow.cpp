#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "ExcelOperation.h"

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
    int row = 1;

    ExcelOperation excelFile("E:\\Git\\QtUi\\TestDoc\\testEx.xlsx", "Sheet3");

    this->readXml = new ReadFile("E:\\Git\\QtUi\\TestDoc\\TempDocx.xml");

    for(int i = 0; i < this->readXml->fileDir.size(); i++)
    {
        for(int j = 0; j < this->readXml->fileDir[i].size(); j++)
        {
            for(int k = 0; k < this->readXml->fileDir[i][j].size(); k++)
            {
                qDebug() << "Dir[" << i <<"][" << j << "][" << k << "]" << this->readXml->fileDir[i][j][k];
                //excelFile.ExcelWriteExcel(row, j+1, this->readXml->fileDir[i][j][k]);
                row++;
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete this->readXml;
    delete ui;
}

