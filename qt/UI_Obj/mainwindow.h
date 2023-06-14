#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QPushButton>
#include <readfile.h>

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
    ReadFile* readXml = NULL;
    QVector<QString> imp;

signals:
    void SendLineEditData(QString path);

};
#endif // MAINWINDOW_H
