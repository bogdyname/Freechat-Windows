#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageviewer.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonFL_clicked();

    void on_pushButtonInfo_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
