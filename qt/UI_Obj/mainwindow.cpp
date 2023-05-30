#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Set background picture. */
    this->setStyleSheet("border-image: url(:/ui_picture/Rabbit.jpg)");


    QPalette palette = ui->lineEdit->palette();
    //palette.setColor(QPalette::Base, QColor(255, 0, 0));
    palette.setColor(QPalette::Base, QColor(255, 0, 0, 255));// # 设置背景颜色不透明
    ui->lineEdit->setAutoFillBackground(true);
    ui->lineEdit->setPalette(palette);



    //connect(ui->pushButton, &QPushButton::clicked,this, &MainWindow::MyPrintf);

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

