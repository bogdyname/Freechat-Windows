#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageviewer.h"
#include <QMessageBox>

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
    QMessageBox::critical(this, "Friend list", "TEST FRIEND LIST");
}
