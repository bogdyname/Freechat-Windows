#include "mainwindow.h"

ImageViewer::ImageViewer()
 {
    QWidget wgt;

     imageLabel = new QLabel;
     imageLabel->setBackgroundRole(QPalette::Base);
     imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel->setScaledContents(true);

     scrollArea = new QScrollArea;
     scrollArea->setBackgroundRole(QPalette::Dark);
     scrollArea->setWidget(imageLabel);
     setCentralWidget(scrollArea);

     createActions();
     createMenus();

     wgt.setWindowTitle(tr("/freechat.jpg"));
     wgt.resize(500, 400);
 }
