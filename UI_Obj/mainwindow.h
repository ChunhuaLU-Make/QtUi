#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QPushButton>
#include "SigDistribution.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int a = 0;
    QString GetLineEditData(void);

private:
    Ui::MainWindow *ui;
    QTimer *timer = NULL;
    SigDistribution* sigDis = NULL;
    QVector<QString> imp;



private slots:
    /* Click start signal.*/
    void ClickStart(void);

signals:
    void SendSrcFileName(QString path);

};
#endif // MAINWINDOW_H
