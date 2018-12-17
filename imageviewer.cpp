#include <QtGui>
#include "imageviewer.h"

ImageViewer::ImageViewer()
{
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

         setWindowTitle(tr("Freechat"));
         resize(500, 400);
}
