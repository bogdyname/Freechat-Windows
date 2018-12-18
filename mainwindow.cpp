#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageviewer.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonFL_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Friend list", "TEST FRIEND LIST",
                                                              QMessageBox:: Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
    else
    {
        qDebug() << "Friend list is empty";
    }
}
