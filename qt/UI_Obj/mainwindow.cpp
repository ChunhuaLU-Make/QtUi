#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "readfile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked,this, &MainWindow::MyPrintf);
}

void MainWindow::MyPrintf(void)
{
    ReadFile reader;
    reader.readFile("C:\\Users\\16924\\Desktop\\oldBig\\learn.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}

