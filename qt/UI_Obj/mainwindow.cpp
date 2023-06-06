#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QPalette>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#if 0
    QPushButton* but = new QPushButton(this);
    but->setText("hello");

    connect(but, &QPushButton::released, this,
            [=]()
            {
                but->setStyleSheet("color : rgba(0, 0, 0, 100)");

                qDebug() << "Hello world:" << a << b;
            }
            );
    qDebug() <<"a" << a;


#endif
    this->resize(500,500);

}


void MainWindow::paintEvent(QPaintEvent* tempP)
{
    QPainter p;
    p.begin(this);
    p.drawPixmap(0,0,width(),height(), QPixmap(":./ui_picture/Rabbit.jpg"));
    p.end();
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

