#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QPalette>
#include <QPainter>
#include "readfile.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    imp.append("#MainWindow{border-image: url(:/ui_picture/dog.png);}");
    imp.append("#MainWindow{border-image: url(:/ui_picture/family1.jpg);}");
    imp.append("#MainWindow{border-image: url(:/ui_picture/family2.jpg);}");
    imp.append("#MainWindow{border-image: url(:/ui_picture/family3.jpg);}");
    imp.append("#MainWindow{border-image: url(:/ui_picture/Rabbit.jpg);}");

    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);

    /* Create timer.*/
    timer = new QTimer(this);

    readXml = new ReadFile();

    ui->lineEdit->setStyleSheet("QLineEdit{background-color:transparent;color:rgb(255,0,0)}");

    QFont textFont("STKaiti",16);
    ui->textEdit->setStyleSheet("QTextEdit{background-color:transparent;color:rgb(0,128,255)}");
    ui->textEdit->setFont(textFont);
    ui->textEdit->moveCursor(QTextCursor::End);

    QFont font("STKaiti",14);
    //设置label背景颜色 ， 字体颜色
    ui->label->setStyleSheet("color:rgb(204,204,0);");   //Red, Green, blue
    ui->label->setFont(font);


    /*Picture nex. */
    connect(timer, &QTimer::timeout, this,
    [=]()
    {
        QString path = imp[a];
        this->setStyleSheet(QString::fromUtf8(path.toUtf8()));
        a++;
        a = a < imp.size()?a:0;

        //SendSignalOutput(QString::number(a)+'\n');

    });

    /* Start timer, set timeout time is 3s. */
    timer->start(3000);

    connect(this, &MainWindow::SendLineEditData, readXml, &ReadFile::ReadFileSlot);

    connect(ui->pushButton, &QPushButton::clicked, this, [=]()
    {
        QString path = GetLineEditData();
        if(path.isEmpty()) return;
        //Send signale, transmit linEdit data.
        emit SendLineEditData(path);

        /* Start readXml thread */
        readXml->start();
    });

    connect(readXml, &ReadFile::MyPrintfSig, ui->textEdit, [=](const QString& text)
            {
        ui->textEdit->insertPlainText(text);
        ui->textEdit->moveCursor(QTextCursor::End);
    });

    /* XiGou call end last call send destroyed signal. */
    connect(this, &MainWindow::destroyed, this, [=]()
    {
        if(readXml->isRunning() == true)
        {
            /* Release resources*/
            readXml->quit();
            readXml->wait();
            readXml->deleteLater(); //delete readXml.
            delete readXml;
        }
    });

}


QString MainWindow::GetLineEditData(void)
{
    return ui->lineEdit->text();
}


MainWindow::~MainWindow()
{
    delete ui;
    qDebug() <<"This is MainWindow xigou";
}

