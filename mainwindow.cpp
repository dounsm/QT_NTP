#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QUdpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timegetter = new MQTimeGetter(this,"ntp.sjtu.edu.cn");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(getTime()));
    connect(timegetter->eventTimer,SIGNAL(timeout()),this,SLOT(showTime()));
}

void MainWindow::getTime(){
    ui->textEdit->append("+\n");
    timegetter->getTime();
};

void MainWindow::showTime(){
    timegetter->eventTimer->stop();
    ui->textEdit->append(".\n");
    ui->textEdit->append(timegetter->time.toString());
};

MainWindow::~MainWindow()
{
    delete ui;
    delete timegetter;
}

