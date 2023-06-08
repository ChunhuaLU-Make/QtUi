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
    imp.append(":/ui_picture/dog.png");
    imp.append(":/ui_picture/family1.jpg");
    imp.append(":/ui_picture/family2.jpg");
    imp.append(":/ui_picture/family3.jpg");
    imp.append(":/ui_picture/Rabbit.jpg");

    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this,
    [=]()
    {
        QString str = (QString)imp.value(a);
        ui->label->setPixmap(QPixmap(str.toUtf8()));

        a++;
        a = a < imp.size()?a:0;
    });
    timer->start(3000);

    connect(ui->Start, &QPushButton::released, this, &MainWindow::MyPrintf);
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

