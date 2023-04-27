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
    reader.readFile("E:\\Git\\QtUi\\TestDoc\\Total.xml");
}

MainWindow::~MainWindow()
{
    delete ui;
}

