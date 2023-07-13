#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QPalette>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QFileDialog>


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

    QFont textFont("Microsoft YaHei",16);
    ui->textEdit->setStyleSheet("QTextEdit{background-color:transparent;color:rgb(0,128,255)}");
    ui->textEdit->setFont(textFont);
    ui->textEdit->moveCursor(QTextCursor::End);

    QFont font("Microsoft YaHei",14);

    //Set the label background colour. font colour.
    ui->radioButton->setStyleSheet("QRadioButton{background-color:transparent;color:rgb(195, 255, 104)}"); //Red, Green, blue
    ui->radioButton->setFont(font);
    ui->radioButton_2->setStyleSheet("QRadioButton{background-color:transparent;color:rgb(195, 255, 104)}");
    ui->radioButton_2->setFont(font);

    ui->pushButton->setFont(font);

    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::ClickStart);

    sigDis = new SigDistribution();

    /* Set word swithc to excel. */
    connect(ui->radioButton, &QRadioButton::pressed, sigDis, &SigDistribution::RadioInforWtoE);

    /* Set Excel switch to word. */
     connect(ui->radioButton_2, &QRadioButton::pressed, sigDis, &SigDistribution::RadioInforEtoW);


    /*Picture next. */
    connect(timer, &QTimer::timeout, this,
    [=]()
    {
        //QString path = imp[a];
        //this->setStyleSheet(QString::fromUtf8(path.toUtf8()));
        a++;
        a = a < imp.size()?a:0;

    });

    /* Start timer, set timeout time is 3s. */
    timer->start(3000);

    /* Send file name to ReadFile. */
    connect(this, &MainWindow::SendSrcFileName, sigDis, &SigDistribution::ReadFileSlot);

    /* Print information to TextEdit. */
    connect(sigDis, &SigDistribution::MyPrintfSig, ui->textEdit, [=](const QString& text)
            {
        ui->textEdit->insertPlainText(text);
        ui->textEdit->moveCursor(QTextCursor::End);
    });

    /* XiGou call end last call send destroyed signal. */
    connect(this, &MainWindow::destroyed, this, [=]()
    {
        if(sigDis->isRunning() == true)
        {
            /* Release resources*/
            sigDis->quit();
            sigDis->wait();
            sigDis->deleteLater(); //delete readXml.
            delete sigDis;
        }
    });
}

void MainWindow::ClickStart(void)
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("open a file."),
        "C:/",
        tr("Word Document(*.docx *.doc *.xml)"));

    if(fileName.isEmpty() == false)
    {
        /* Send file name. */
        emit SendSrcFileName(fileName);

        /* Start readXml thread */
        sigDis->start();

        qDebug() <<"FaileName:" << fileName;
    }
}

QString MainWindow::GetLineEditData(void)
{
    return "eh"; //ui->lineEdit->text();
}


MainWindow::~MainWindow()
{
    delete ui;
    qDebug() <<"This is MainWindow xigou";
}

